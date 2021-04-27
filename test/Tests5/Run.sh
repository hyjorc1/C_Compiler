#!/bin/bash

TIMEOUT=30
SCRIPT=$0
MODE=5
DASHO=""
FLAGS=""
GENERATE=""
ASSEMBLE="assemble.py"
DETAIL=""

usage() 
{
  echo "Usage: $SCRIPT executable [options] infile infile ..."
  echo "Any infile without corresponding output files will be skipped"
  echo "Options: "
  echo "  -c S: Use additional compiler switches in string S"
  echo "  -d:   more detailed comparison"
  echo "  -g:   generate test outputs"
  echo "  -o:   use -o instead of stdout to collect output"
  echo "  -t N: set timeout to N seconds (default is $TIMEOUT)"
  echo "        0 seconds uses no timeout"
  exit $1
}

green()
{
  printf "[1;32m$1[0;39m$2"
}

yellow()
{
  printf "[1;33m$1[0;39m$2"
}

red()
{
  printf "[1;31m$1[0;39m$2"
}

striplines()
{
  sed -n 's/^Error.*line *\([0-9]*\).*/Error \1/p'
}

# Arg1: error file
firstError()
{
  awk '/^Error.*line *[0-9]*/ { errors++; if (errors>1) exit }\
                              { if (errors) print }' $1
}

# Arg1: base source file 
generateOuts()
{
  echo "Generating files for $1.c"
  ./$EXE -$MODE $FLAGS -o $1.j $1.c 2> $1.error.txt
  if [ -s $1.error.txt ]; then
    rm $1.j
    green "    $1.error.txt" "\n"
    return 0
  fi
  rm $1.error.txt
  if $ASSEMBLE $1.j > /dev/null; then
    rm $1.j
    errs=0
    lastin=""
    for infile in $1.input*; do
      if [ ! -f $infile ]; then
        continue
      fi
      lastin="$infile"
      outfile=`sed "s/$1.input/$1.output/" <<< $infile` 
      if java $1 < $infile > $outfile; then
        green "    $outfile" "\n"
      else
        red "    ERROR on input $infile" "\n"
        rm $outfile
        errs=$[ errs + 1 ]
      fi
    done
    if [ ! "$lastin" ]; then
# No input files; that means the program does not take input.
      outfile=$1.output
      if java $1 > $outfile; then
        green "    $outfile" "\n"
      else
        red "    ERROR for no input" "\n"
        rm $outfile
        errs=$[ errs + 1 ]
      fi
    fi
    if [ $errs -eq 0 ]; then
      rm $1.class
    else
      yellow "    Retaining $1.class" "\n"
    fi
    return 0
  fi
  red "    Error assembling $1.j" "\n"
}

# Arg1: PID to wait for
# Arg2: timeout message
timeout()
{
  PID=$1
  if [ $TIMEOUT -lt 1 ]; then
    wait
    return 0
  fi
  disown -r 
# ^ avoid messages if we kill the process
  killsignal=""
  SECONDS=0
  while true; do
    sleep 1
    if ps $PID > /dev/null; then
      # still running
      if [ $SECONDS -gt $TIMEOUT ]; then
        if [ "$2" ]; then
          red "$2"
        fi
        if [ $killsignal ]; then
          kill $killsignal $PID
        else
          kill $PID  
          killsignal="-9"
        fi
      fi
    else
      # completed
      return 0
    fi
  done
}

# Arg1: input file
# Arg2: output file
# Arg3: error file
timeoutCompile()
{
  infile=$1
  outfile=$2
  errfile=$3
  if [ $DASHO ]; then
    nice ./$EXE -$MODE $FLAGS -o $outfile $infile 2> $errfile &
    timeout $! "Timeout exceeded"
  else
    nice ./$EXE -$MODE $FLAGS $infile 1> $outfile 2> $errfile &
    timeout $! "Timeout exceeded"
  fi
}

# Arg1: java class
# Arg2: output file
# Arg3: input file or empty
timeoutJava()
{
  if [ "$3" ]; then
    nice java $1 > $2 < $3 &
  else
    nice java $1 > $2 &
  fi
  timeout $! "Timeout exceeded\n        "
}

# Arg1: base
testError()
{
  cp -p $1.c $1.c.backup
  echo "" > student.error.txt
  printf "$1.c"
  timeoutCompile $1.c /dev/null student.error.txt
  printf "\n"
  if diff -q $1.c $1.c.backup > /dev/null; then
    rm $1.c.backup
  else
    red "    Input file mangled, restoring" "\n"
    mv -f $1.c.backup $1.c
  fi
  firstoracle=`firstError $1.error.txt`
  firststudent=`firstError student.error.txt`

  if [ "$firstoracle" == "$firststudent" ]; then
    green "    Errors match" "\n"
    rm student.error.txt
    return 0
  fi
  
  lineoracle=`striplines <<< "$firstoracle"`
  linestudent=`striplines <<< "$firststudent"`
  if [ ! "$linestudent" ]; then
    red "    Did not catch error?" "\n"
  elif [ "$lineoracle" == "$linestudent" ]; then
    yellow "    First error messages have matching line numbers" "\n"
  else
    red "    First errors have different line numbers" "\n"
  fi
  if [ "$DETAIL" ]; then
    echo "         Expected first error:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' <<< "$firstoracle"
    echo "         ---------------------------------------------------------"
    echo
    echo "         Given first error:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' <<< "$firststudent"
    echo "         ---------------------------------------------------------"
    echo "         Complete error stream given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' student.error.txt
    echo "         ---------------------------------------------------------"
  fi
  rm student.error.txt
}

# Arg1: base
# Arg2: outfile
# Arg3: infile or missing
#
compareOut()
{
  if [ ! -f $2 ]; then
    return 0
  fi
  showinput=""
  if [ "$3" ]; then
    showinput=" on input $3"
  fi
  printf "    "
  echo "" > student.out.txt
  timeoutJava $1 student.out.txt $3
  if diff -q student.out.txt $2 > /dev/null; then
    green "output matches" "$showinput\n"
  else
    red "output differs" "$showinput\n"
    if [ "$DETAIL" ]; then
      echo "         Expected output:"
      echo "         ---------------------------------------------------------"
      awk '{print "         | " $0}' $2
      echo "         ---------------------------------------------------------"
      echo
      echo "         Given output:"
      echo "         ---------------------------------------------------------"
      awk '{print "         | " $0}' student.out.txt
      echo "         ---------------------------------------------------------"
    fi
  fi 
  rm student.out.txt
}

# Arg1: base
testOuts()
{
  cp -p $1.c $1.c.backup
  echo "" > student.error.txt
  echo "" > $1.j
  printf "$1.c"
  timeoutCompile $1.c $1.j student.error.txt
  printf "\n"
  if diff -q $1.c $1.c.backup > /dev/null; then
    rm $1.c.backup
  else
    red "    Input file mangled, restoring" "\n"
    mv -f $1.c.backup $1.c
  fi
  if [ -s student.error.txt ]; then
    red  "    Unexpected compile error" "\n"
    echo "         Complete error stream given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' student.error.txt
    echo "         ---------------------------------------------------------"
    rm student.error.txt $1.j
    return 0
  fi
  rm student.error.txt
  green "    No compile errors" ", running assembler\n"
  if $ASSEMBLE $1.j | awk -v p="$DETAIL" '{if (p=="y") print "\t\t" $0}'; then
    green "    Target code assembles" ", running tests\n"
    rm $1.j
  else
    red "    Target code assembly failed" "\n"
    rm $1.j
    return 0
  fi

  lastin=""
  for infile in $1.input*; do
    if [ ! -f $infile ]; then
      continue
    fi
    lastin="$infile"
    outfile=`sed "s/$1.input/$1.output/" <<< $infile` 
    compareOut $1 $outfile $infile
  done
  if [ ! "$lastin" ]; then
# No input files; that means the program does not take input.
    compareOut $1 $1.output
  fi

  rm $1.class
}

bailout()
{
  echo 
  echo "Caught CTRL-C, terminating script"
  echo
  exit 1
}


#############################################################

trap bailout INT

if [ $# -eq 0 ]; then
  usage 0
fi

EXE=$1
shift

if [ ! -x $EXE ]; then
  echo "Can't execute $EXE"
  usage 1
fi

if [ ! -f libc.class ]; then
  javac libc.java
fi

echo Running tests using compiler:
./$EXE -0 | awk '{print "  | " $0}'

echo " "

Fnext=""
TOnext=""
for arg; do

# check for options/switches

  if [ $TOnext ]; then
    TIMEOUT=$arg
    TOnext=""
    continue
  fi

  if [ $Fnext ]; then
    FLAGS=$arg
    Fnext=""
    continue
  fi

  case "$arg" in
    -[4-5])
        MODE=$[ -arg ]
        continue
        ;;

    -c)
        Fnext="y"
        continue
        ;;

    -d)
        DETAIL="y"
        continue
        ;;

    -g)
        GENERATE="y"
        continue
        ;;

    -o)
        DASHO="y"
        continue
        ;;

    -t)
        TOnext="y"
        continue
        ;;

  esac

  if [ ! -f $arg ]; then
    continue
  fi

  BASE=`basename -s .c $arg`
  if [ ! -f $BASE.c ]; then
    continue
  fi

  if [ $GENERATE ]; then
    generateOuts $BASE
    continue
  fi

  if [ -f $BASE.error.txt ]; then
    testError $BASE
    continue
  fi

  testOuts $BASE
done

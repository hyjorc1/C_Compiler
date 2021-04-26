#!/bin/bash

TIMEOUT=30
SCRIPT=$0
MODE=4

usage()
{
  echo "Usage: $SCRIPT executable infile infile ..."
  echo
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

bailout()
{
  echo 
  echo "Caught CTRL-C, terminating script"
  echo
  exit 1
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
    nice ./$MYCC -$MODE $FLAGS -o $outfile $infile 2> $errfile &
    timeout $! "Timeout exceeded"
  else
    nice ./$MYCC -$MODE $FLAGS $infile 1> $outfile 2> $errfile &
    timeout $! "Timeout exceeded"
  fi
}



showMethod()
{
  echo "            Extracted method:"
  echo "            ----------------------------------------------------"
  read line
  yellow "            | $line" "\n"
  read line
  yellow "            |   $line" "\n"
  if read lineA; then
# Dummy
    line=""
  else
    return 0
  fi
  if read lineB; then
#Dummy
    line=""
  else
    yellow "            | $lineA" "\n"
    return 0
  fi
  while read line; do
    echo "            |     $lineA"
    lineA="$lineB"
    lineB="$line"
  done
  yellow "            |   $lineA" "\n"
  yellow "            | $lineB" "\n"
  echo "            ----------------------------------------------------"
}

# Arg1: method name
# Arg2: file
stripMethod()
{
  sed -n "/.method.* $1/,/.end.*method/p" $2
}

# Arg1: method name
# Arg2: basename
checkMethod()
{
  ALLGOOD="y"
  echo "        Checking method $f"
  METHLINE=`stripMethod $1 $2.j | head -n 1`
  CODELINE=`stripMethod $1 $2.j | awk '{if (NR==2) print}'`
  ENDCODE=`stripMethod $1 $2.j | tail -n 2 | head -n 1`
  ENDMETH=`stripMethod $1 $2.j | tail -n 1`

  if [ ! "$METHLINE" ]; then
    red "            Not found" "; check .j file\n"
    return 0
  fi

  STUTYPE=`awk '{print $NF}' <<< "$METHLINE"`
  ANSTYPE=`grep "/// $1" $2.c  | awk '/types/{print $4}'`

  printf "            Parameter and return types: "
  if [ "$STUTYPE" == "$ANSTYPE" ]; then
    green "matches" "\n"
  else
    red "differs/missing" "\n"
    printf "\t\tExpected: $ANSTYPE\n"
    printf "\t\tStudent : $STUTYPE\n"
    ALLGOOD=""
  fi

  printf "            .method line without types: "
  if grep " *[.]method *public *static *$1" <<< "$METHLINE" > /dev/null; then
    green "matches" "\n"
  else
    red "differs/missing" "\n"
    ALLGOOD=""
  fi
  printf "            .end method line          : "
  if grep " *[.]end *method" <<< "$ENDMETH" > /dev/null; then
    green "matches" "\n"
  else
    red "differs/missing" "\n"
    ALLGOOD=""
  fi

  read CODE STACK STUSTK LOCALS STULOC DONE <<< "$CODELINE"
  printf "            .code line format         : "
  if [ "$CODE" == ".code" -a "$STACK" == "stack" -a "$LOCALS" == "locals" -a "x$DONE" == "x" ]; then
    green "matches" "\n"
  else
    red "differs/missing" "\n"
    ALLGOOD=""
  fi

  read END CODE DONE <<< "$ENDCODE"
  printf "            .end code line            : "
  if [ ".end" == "$END" -a "$CODE" == "code" -a "x$DONE" == "x" ]; then
    green "matches" "\n"
  else
    red "differs/missing" "\n"
    ALLGOOD=""
  fi

  ANSSTK=`grep "/// $1" $2.c  | awk '/stack/{print $4}'`
  ANSLOC=`grep "/// $1" $2.c  | awk '/locals/{print $4}'`

  printf "            reasonable stack limit    : "
  gup=$[ ANSSTK + 4 ]
  yup=$[ ANSSTK + 7 ]
  ydn=$[ ANSSTK - 2 ]
  if [ "$STUSTK" -ge "$ANSSTK" -a "$STUSTK" -le "$gup" ]; then
    green "looks good" 
  elif [ "$STUSTK" -ge "$ydn" -a "$STUSTK" -le "$yup" ]; then
    yellow "a bit off " 
  else
    red "suspicous "
    ALLGOOD=""
  fi
  printf " (expected $ANSSTK, got $STUSTK)\n"

  printf "            correct local count       : "
  if [ "$STULOC" -eq "$ANSLOC" ]; then
    green "matches" "\n"
  else
    red "differs" " (expected $ANSLOC, got $STULOC)\n"
    ALLGOOD=""
  fi

  if [ "$ALLGOOD" ]; then
    return 0
  fi

  stripMethod $1 $2.j | showMethod
}

# Arg1: source file
processFile()
{
  if [ ! -f $1 ] ; then
    return 0
  fi

  base=`basename -s .c $1`
  if [ ! -f $base.c ]; then
    return 0
  fi

  funclist=`awk '/\/\/\/ USER/{ print $3}' $1 | xargs`

  if [ ! "$funclist" ]; then
    return 0
  fi

  cp -p $base.c $base.c.backup
  echo "" > student.error.txt
  echo "" > $base.j
  echo "$1"
  timeoutCompile $base.c $base.j student.error.txt
  if diff -q $base.c $base.c.backup > /dev/null; then
    rm $base.c.backup
  else
    red "    Input file mangled, restoring" "\n"
    mv -f $base.c.backup $base.c
  fi
  if [ -s student.error.txt ]; then
    red  "    Unexpected compile error" "\n"
    echo "         Complete error stream given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' student.error.txt
    echo "         ---------------------------------------------------------"
    rm student.error.txt $base.j
    return 0
  fi
  green "    No compile errors" "\n"

  for f in $funclist; do
    checkMethod $f $base
  done
  rm $base.j
}

if [ $# -lt 1 ]; then
  usage 0
fi

MYCC=$1
shift

if [ ! -x $MYCC ]; then
  echo "Can't execute $MYCC"
  usage 1
fi

echo Running tests using compiler:
./$MYCC -0 | awk '{print "  | " $0}'
echo " "

for args; do
  processFile $args
done

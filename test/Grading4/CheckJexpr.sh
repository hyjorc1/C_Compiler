#!/bin/bash

TIMEOUT=30
SCRIPT=$0
MODE=4
JEXPR="../Jexpr/jexpr -V"
CODE="CODE"
TESTS="B"
MYCC=""
OPTIONS=""

CHECK=""
NOCOMPILE=""

usage()
{
  echo "Usage: $SCRIPT executable (switches) infile infile ..."
  echo 
  echo "Supported switches: "
  echo "    -J  : Jexpr only"
  echo "    -A  : Assembly only"
  echo "    -B  : Both Jexpr and Assembly (default)"
  echo "    -O option : invoke compiler with given option string"
  echo
  exit $1
}

green()
{
  printf "[1;32m%s[0;39m%s\n" "$1" "$2"
}

yellow()
{
  printf "[1;33m%s[0;39m%s\n" "$1" "$2"
}

red()
{
  printf "[1;31m%s[0;39m%s\n" "$1" "$2"
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
    nice ./$MYCC -$MODE $OPTIONS -o $outfile $infile 2> $errfile &
    timeout $! "Timeout exceeded"
  else
    nice ./$MYCC -$MODE $OPTIONS $infile 1> $outfile 2> $errfile &
    timeout $! "Timeout exceeded"
  fi
}


showMethod()
{
  echo "            ----------------------------------------------------"
  read line
  echo "            | $line" 
  read line
  echo "            |   $line" 
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
    echo "            | $lineA" 
    return 0
  fi
  while read line; do
    yellow "            |     $lineA" 
    lineA="$lineB"
    lineB="$line"
  done
  echo "            |   $lineA" 
  echo "            | $lineB" 
  echo "            ----------------------------------------------------"
}

# Arg1: method name
# Arg2: file
stripMethod()
{
  sed -n "/.method.* $1/,/.end.*method/p" $2
}

# Arg1: string of comma-separated regexes to look for
# standard input: file to read from
# return 0 if found, 1 otherwise
findSeq()
{
  if [ ! "$1" ]; then
    return 1
  fi
  STEP=1
  while read line; do
    SEQ=`awk -F, -v N=$STEP '{print $N}' <<< "$1"`
    if [ ! "$SEQ" ]; then
      return 0
    fi
    if egrep "$SEQ" <<< "$line" > /dev/null; then
      STEP=$[STEP + 1]
    else
      STEP=1
    fi
  done
  return 1
}

# Arg1: State
# Arg2: string of comma-separated regexes
prettySequence()
{
  SEQ=`awk -F, '{print $1}' <<< "$2"`
  if [ "matched" == "$1" ]; then
      green "                $1: " "$SEQ"
  else
      yellow "                $1: " "$SEQ"
  fi
  N=2
  while true; do
    SEQ=`awk -F, -v N=$N '{print $N}' <<< "$2"`
    if [ ! "$SEQ" ]; then
      echo
      return 0
    fi
    printf "                         %s\n" "$SEQ"
    N=$[N+1]
  done
}

# Arg1: method name
# Arg2: "expr" or "code"
# Arg3: input file
# return 0 if all match, 1 otherwise
checkItems()
{
  allok="y"
  state="norm"
# States are
#   norm  : keep reading until matching comment
#   expr  : expr portion of comment
#   code  : code portion of comment
#   pass  : we already passed this test case
  instr=""
  while read item; do
    # echo "state $state, got line $item"
    if [ ! "$item" ]; then
      continue
    fi
    if [ "$state" == "norm" ]; then
      if grep "/\*\* $1" <<< "$item" > /dev/null; then
        instr=`awk -F/\*\* '{print $1}' <<< "$item"`
        state="expr"
        echo "            Checking instruction $instr"
      fi
      continue
    fi
    if [ "**/" == "$item" ]; then
      if [ "$state" != "pass" ]; then
        red "            No matches" " for $instr"
        allok=""  
      fi
      state="norm"
      continue
    fi
    if [ "pass" == "$state" ]; then
      continue
    fi
    if [ "CODE" == "$item" ]; then
      state="code"
      continue
    fi
    if [ "$2" == "$state" ]; then
      if findSeq "$item" < $3; then
        prettySequence "matched" "$item"
        state="pass"
      else
        prettySequence "missing" "$item"
      fi
    fi
  done
  if [ "$allok" ]; then
    return 0
  else
    return 1
  fi
}

# Arg1: method name
# Arg2: basename
checkMethod()
{
  echo "    ======================================================================"
  echo "    Method $f"
  if [ "$TESTS" != "A" ]; then
    echo "        Checking with jexpr"
    $JEXPR -m $1 $2.j 2> /dev/null | sed '/;STACK:/p;/;/d' > $2.exprs
    if checkItems $1 "expr" $2.exprs < $2.c; then
      green  "    PASSED" " $f"
      echo
      rm $2.exprs
      return 0
    fi
    echo
  fi
  if [ "$TESTS" != "J" ]; then
    echo "        Checking assembly"
    stripMethod $1 $2.j | sed 's/;.*//' | grep -v "^ *$" > $2.method

    if checkItems $1 "code" $2.method < $2.c; then
      green  "    PASSED" " $f"
      echo
      rm $2.method
      return 0
    fi
    echo
  fi
  red "    FAILED" " $f; check by hand"

  if [ -f $2.exprs ]; then
    echo "            Extracted method, jexpr:"
    showMethod < $2.exprs
    rm $2.exprs
  fi
  if [ -f $2.method ]; then
    echo "            Extracted method, assembly:"
    showMethod < $2.method
    rm $2.method
  fi
  echo
  return 1
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

  funclist=`awk '/\/\/\/ JEXPR/{$1=""; $2=""; print}' $1 | xargs`

  if [ ! "$funclist" ]; then
    return 0
  fi

  FILEOK="y"

  cp -p $base.c $base.c.backup
  echo "" > student.error.txt
  echo "" > $base.j
  echo "$1"
  timeoutCompile $base.c $base.j student.error.txt
  if diff -q $base.c $base.c.backup > /dev/null; then
    rm $base.c.backup
  else
    red "    Input file mangled, restoring" 
    mv -f $base.c.backup $base.c
  fi
  if [ -s student.error.txt ]; then
    red  "    Unexpected compile error" 
    echo "         Complete error stream given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' student.error.txt
    echo "         ---------------------------------------------------------"
    rm student.error.txt $base.j
    if [ "$NOCOMPILE" ]; then
      NOCOMPILE="$NOCOMPILE;~$1"
    else
      NOCOMPILE="~$1"
    fi
    return 0
  fi
  green "    No compile errors" 
  rm student.error.txt

  for f in $funclist; do
    if checkMethod $f $base; then
      dummy="hi"
    else
      FILEOK=""
    fi
  done
  rm $base.j

  if [ ! "$FILEOK" ]; then
    if [ "$CHECK" ]; then
      CHECK="$CHECK;~$1"
    else
      CHECK="~$1"
    fi
  fi
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


dasho=""
for args; do
  if [ "$dasho" ]; then
    OPTIONS="$args"
    dasho=""
    continue
  fi
  if [ "$args" == "-J" -o "$args" == "-B" -o "$args" == "-A" ]; then
    TESTS=`echo "$args" | tr -d '-'` 
    continue
  fi
  if [ "$args" == "-O" ]; then
    dasho="y"
    continue
  fi
  processFile $args
done
echo "======================================================================"
if [ "$CHECK" ]; then
  echo "The following test files need to be checked by hand:"
  echo "$CHECK" | tr ';~' '\n\t'
fi
if [ "$NOCOMPILE" ]; then
  echo "The following test files had unexpected compile errors:"
  echo "$NOCOMPILE" | tr ';~' '\n\t'
fi

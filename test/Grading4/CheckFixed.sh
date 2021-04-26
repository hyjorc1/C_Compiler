#!/bin/bash

TIMEOUT=30
SCRIPT=$0
MODE=4
JEXPR="./jexpr"

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
    nice ./$EXE -$MODE $FLAGS -o $outfile $infile 2> $errfile &
    timeout $! "Timeout exceeded"
  else
    nice ./$EXE -$MODE $FLAGS $infile 1> $outfile 2> $errfile &
    timeout $! "Timeout exceeded"
  fi
}

# Arg1: what
# Arg2: code; 0 is good
summaryLine()
{
  printf "$1"
  if [ "$2" -eq "0" ]; then
    green "matches" "\n"
  else
    red "differs" "\n"
  fi
}


# Arg1: base name
testClass()
{
  code=0
  printf "\t.class public: "
  read dotclass public classname rest
  if [ "$dotclass" == ".class" -a "$public" == "public" ]; then
    green "good" "\n"
    printf "\t class name  : "
    if [ "$classname" == "$1" ]; then
      green "good" "\n"
    else
      red "missing or incorrect" "\n"
      code=1
    fi
  else
    red "missing or incorrect" "\n"
    code=1
  fi

  if [ "$code" == "1" ]; then
    printf "\tExpected line: .class public $1\n"
    printf "\tStudent line : $dotclass $public $classname $rest\n"
  fi

  printf "\t.super       : "
  read line2
  if [ "$line2" == ".super java/lang/Object" ]; then
    green "good" "\n"
    return $code
  else
    red "missing or incorrect" "\n"
    printf "\tExpected line: .super java/lang/Object\n"
    printf "\tStudent line : $line2\n"
    return 1
  fi
}

expectedInit()
{
  cat <<EOF
.method public static <init> : ()V
    .code stack 1 locals 1
        aload_0
        invokespecial Method java/lang/Object <init> ()V
        return
    .end code
.end method
EOF
}

# Arg1: basename
expectedMain()
{
  cat <<EOF
.method public static main : ([Ljava/lang/String;)V
    .code stack 2 locals 2
EOF
  echo "        invokestatic Method $1 main ()I"
  cat <<EOF
        istore_1
        getstatic Field java/lang/System out Ljava/io/PrintStream;
        ldc 'Return code: '
        invokevirtual Method java/io/PrintStream print (Ljava/lang/String;)V
        getstatic Field java/lang/System out Ljava/io/PrintStream;
        iload_1
        invokevirtual Method java/io/PrintStream println (I)V
        return
    .end code
.end method
EOF
}

# Arg1: basename 
testInit()
{
  $JEXPR -j -m "<init>" $1.j | sed -n "/.method/,/.end method/p" > $1.j.init

  if expectedInit | diff -q -w $1.j.init - > /dev/null; then
    INIT=0
  else
    INIT=1
    echo "         Expected:"
    echo "         ---------------------------------------------------------"
    expectedInit | awk '{print "         | " $0}' 
    echo "         ---------------------------------------------------------"
    echo
    echo "         Given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' < $1.j.init
    echo "         ---------------------------------------------------------" 
  fi
  rm $1.j.init
  return $INIT
}

# Arg1: basename 
testMain()
{
  $JEXPR -j -m "main" $1.j | sed -n "/main.*String/,/end method/p" > $1.j.main

  if expectedMain $1 | diff -q -w $1.j.main - > /dev/null; then
    MAIN=0
  else
    MAIN=1
    echo "         Expected:"
    echo "         ---------------------------------------------------------"
    expectedMain $1 | awk '{print "         | " $0}' 
    echo "         ---------------------------------------------------------"
    echo
    echo "         Given:"
    echo "         ---------------------------------------------------------"
    awk '{print "         | " $0}' < $1.j.main
    echo "         ---------------------------------------------------------" 
  fi
  rm $1.j.main
  return $MAIN
}


# Arg1: base
testFixed()
{
  cp -p $1.c $1.c.backup
  echo "" > student.error.txt
  echo "" > $1.j
  printf "$1.c\n"
  timeoutCompile $1.c $1.j student.error.txt
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
  green "    No compile errors" "\n"

  printf "    Checking header\n"
  $JEXPR -j -m " " $1.j  | grep -v "^$" | testClass $1
  CLASS=$?

  printf "    Checking init method\n"
  testInit $1
  INIT=$?

  printf "    Checking main method\n"
  testMain $1
  MAIN=$?

  rm student.error.txt $1.j

  echo "    Summary:"
  summaryLine "\tClass with proper name; super      " $CLASS
  summaryLine "\tSpecial method <init>              " $INIT
  summaryLine "\tJava main() method                 " $MAIN
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

echo Running tests using compiler:
./$EXE -0 | awk '{print "  | " $0}'

echo " "

for arg; do
  BASE=`basename -s .c $arg`
  if [ ! -f $BASE.c ]; then
    continue
  fi
  if [ -f $BASE.error.txt ]; then
    continue
  fi

  testFixed $BASE
done

#!/bin/bash

TIMEOUT=30
SCRIPT=$0
MODE=5
MYCC=""
OPTIONS=""
BUILDJ="y"

CHECK=""
NOCOMPILE=""

debug()
{
#  echo "$1"
  return
}

usage()
{
  echo "Usage: $SCRIPT executable (switches) infile infile ..."
  echo 
  echo "Supported switches: "
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

# Arg1: string to compare
# Remaining args: what to compare against
unique()
{
  key=$1
  shift
  for args; do
    if [ "$key" == "$args" ]; then
      return 1
    fi
  done
  return 0
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
  LA=""
  LB=""
  LC=""
  LD=""
  OPTIONAL=""
  while read line; do
    if [ ! "$line" ]; then
      continue
    fi
    debug "Read line $line"

    while true; do 

      SEQ=`awk -F, -v N=$STEP '{print $N}' <<< "$1"`
      if [ ! "$SEQ" ]; then
        return 0
      fi
      debug "    checking $SEQ"

      # special case: placeholder labels
      if grep "LA" <<< "$SEQ" > /dev/null; then
        if [ ! "$LA" ]; then
          sub=`sed 's|.*\(L[0-9]*\).*|\1|' <<< "$line"`
          if unique $sub $LB $LC $LD; then
            LA="$sub"
          else
            LA="LA"
          fi
        fi
        SEQ=`sed "s|LA|$LA|" <<< $SEQ` 
      fi

      if grep "LB" <<< "$SEQ" > /dev/null; then
        if [ ! "$LB" ]; then
          sub=`sed 's|.*\(L[0-9]*\).*|\1|' <<< "$line"`
          if unique $sub $LA $LC $LD; then
            LB="$sub"
          else
            LB="LB"
          fi
        fi
        SEQ=`sed "s|LB|$LB|" <<< $SEQ` 
      fi

      if grep "LC" <<< "$SEQ" > /dev/null; then
        if [ ! "$LC" ]; then
          sub=`sed 's|.*\(L[0-9]*\).*|\1|' <<< "$line"`
          if unique $sub $LA $LB $LD; then
            LC="$sub"
          else
            LC="LC"
          fi
        fi
        SEQ=`sed "s|LC|$LC|" <<< $SEQ` 
      fi

      if grep "LD" <<< "$SEQ" > /dev/null; then
        if [ ! "$LD" ]; then
          sub=`sed 's|.*\(L[0-9]*\).*|\1|' <<< "$line"`
          if unique $sub $LA $LB $LC; then
            LD="$sub"
          else
            LD="LD"
          fi
        fi
        SEQ=`sed "s|LD|$LD|" <<< $SEQ` 
      fi


      # Is this optional?
      if [ ${SEQ::1} == "?" ]; then
        OPTIONAL="y"
        SEQ="${SEQ:1:100}"
      else
        OPTIONAL=""
      fi

      # Check for match
      if egrep "$SEQ" <<< "$line" > /dev/null; then
        debug "    matched $SEQ"
        STEP=$[STEP + 1]
        break
      fi

      # Ignore any extra labels
      if egrep "L.*:" <<< "$line" > /dev/null; then
        if unique "$line" "$LA:" "$LB:" "$LC:" "$LD:"; then
          debug "    ignored label $line"
          break
        fi
      fi

      # Skip optional matches
      if [ $OPTIONAL ]; then
        debug "    failed optional $SEQ"
        STEP=$[STEP + 1]
        continue
      fi

      debug "    failed $SEQ"
      STEP=1
      LA=""
      LB=""
      LC=""
      LD=""
      break
    done
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
# Arg3: input file
# return 0 if all match, 1 otherwise
checkItems()
{
  allok="y"
  state="norm"
# States are
#   norm  : keep reading until matching comment
#   code  : code portion of comment
#   pass  : we already passed this test case
  instr=""
  while read item; do
    # echo "state $state, got line $item"
    if [ "$state" == "norm" ]; then
      if grep "/\*\* $1" <<< "$item" > /dev/null; then
        instr=`awk -F/\*\* '{print $1}' <<< "$item"`
        state="code"
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
    if [ "code" == "$state" ]; then
      if findSeq "$item" < $2; then
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

  echo "        Checking assembly"
  stripMethod $1 $2.j | sed 's/;.*//' | sed 's/L.*:/&\n/' | grep -v "^ *$" > $2.method

  if checkItems $1 $2.method < $2.c; then
    green  "    PASSED" " $f"
    echo
    rm $2.method
    return 0
  fi
  echo
  red "    FAILED" " $f; check by hand"

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

  funclist=`awk '/\/\/\/ ASSEMBLY/{$1=""; $2=""; print}' $1 | xargs`

  if [ ! "$funclist" ]; then
    return 0
  fi

  FILEOK="y"

  if [ "$BUILDJ" ]; then 
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
  fi

  for f in $funclist; do
    if checkMethod $f $base; then
      dummy="hi"
    else
      FILEOK=""
    fi
  done
  if [ "$BUILDJ" ]; then
    rm $base.j
  fi

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

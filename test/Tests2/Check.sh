#!/bin/bash

TIMEOUT=5
SCRIPT=$0
MODE=2
DASHO=""
SUMMARY=""

usage() 
{
  echo "Usage: $SCRIPT executable [options] infile infile ..."
  echo "Any infile without corresponding output files will be skipped"
  echo "Options: "
  for M in 1 2 3 4 5; do
    if [ $MODE -eq $M ]; then
      echo "  -$M:   test mode $M (default)"
    else
      echo "  -$M:   test mode $M"
    fi
  done
  echo "  -d:   detailed output (default)"
  echo "  -gb:  generate non-extra credit output files"
  echo "  -ge:  generate extra credit output files"
  echo "  -o:   use -o instead of stdout to collect output"
  echo "  -s:   summary output (opposite of -d)"
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

# Arg1: input file
# Arg2: output stub 
timeoutCompile()
{
  infile=$1
  outfile=$2
  if [ $DASHO ]; then
    nice ./$EXE -$MODE -o $outfile.output$MODE $infile 2> $outfile.error$MODE &
    PID=$!
  else
    nice ./$EXE -$MODE $infile 1> $outfile.output$MODE 2> $outfile.error$MODE &
    PID=$!
  fi
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
        red "    Timeout exceeded ($TIMEOUT seconds), terminating"
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

#
# Clean up temp files
#
cleanup()
{
  touch $STUB.output$MODE $STUB.error$MODE $STUB
  rm $STUB.output$MODE $STUB.error$MODE $STUB
}

bailout()
{
  echo 
  echo "Caught CTRL-C, terminating script"
  echo
  cleanup
  exit 1
}

checkDuplicate()
{
  mainfile=$1
  extrafile=$2
  if [ -e $mainfile -a -e $extrafile ]; then
      if diff -b $mainfile $extrafile > /dev/null; then
        echo "  collapsing equal $extrafile"
        rm $extrafile
      fi
  fi
}

# Arg1: oracle output file
# Arg2: actual output file
getOutStatus()
{
  if [ ! -f $1 ]; then
    echo "."
  elif diff -w -q $1 $2 > /dev/null; then
    if [ -s $1 ]; then
      echo "M"
    else
      echo "E"
    fi
  else
    echo "D"
  fi
}

# Arg1: status
# Arg2: type ("basic output" or "extra credit output")
# Arg3: oracle output file
# Arg4: actual output file
detailOut()
{
  if [ "$1" == "." ]; then
    return 0
  fi
  printf "    $2: "
  if [ "$1" == "E" ]; then
    green "both empty" "\n"
    return 0
  fi
  if [ "$1" == "M" ]; then
    green "matches" "\n"
    return 0
  fi
  red "differs" "\n"
  diff -w $3 $4 | awk '{print "     | " $0}'
}


# Arg1: status
# Arg2: type ("basic error" or "extra credit error")
# Arg3: oracle error file
# Arg4: actual error file
detailErr()
{
  if [ "$1" == "." ]; then
    return 0
  fi
  printf "    $2: "
  if [ "$1" == "E" ]; then
    green "both empty" "\n"
    return 0
  fi
  if [ "$1" == "M" ]; then
    green "all match" "\n"
    return 0
  fi
  if [ "$1" == "F" ]; then
    green "1st errors match" "\n"
    return 0
  fi
  if [ "$1" == "L" ]; then
    yellow "1st errors same line numbers" "\n"
  else
    red "different line numbers" "\n"
  fi

  echo "      Expected first error:"
  echo "      ---------------------------------------------------------"
  firstError $3 | awk '{print "      | " $0}'
  echo "      ---------------------------------------------------------"
  echo
  echo "      Given first error:"
  echo "      ---------------------------------------------------------"
  firstError $4 | awk '{print "      | " $0}'
  echo "      ---------------------------------------------------------"
  echo "      Complete error stream given:"
  echo "      ---------------------------------------------------------"
  awk '{print "      | " $0}' $4
  echo "      ---------------------------------------------------------"
}

# Arg1: oracle error file
# Arg2: actual error file
getErrStatus()
{
  if [ ! -f $1 ]; then
    echo "."
    return 0
  fi
  if diff -w -q $1 $2 > /dev/null; then
    if [ -s $1 ]; then
      echo "M"
    else
      echo "E"
    fi
    return 0
  fi
  firstoracle=`firstError $1`
  firstactual=`firstError $2`
  if [ "$firstoracle" == "$firstactual" ]; then
    echo "F"
    return 0
  fi
  
  lineoracle=`striplines <<< "$firstoracle"`
  lineactual=`striplines <<< "$firstactual"`
  if [ "$lineoracle" == "$lineactual" ]; then
    echo "L"
  else
    echo "D"
  fi
}

# Arg1: 
#    E = both outputs are empty 
#    M = all output matches perfectly
#    F = first errors match perfectly
#    L = line numbers match (for first error)
#    D = different
# Arg2: after text
showStatus()
{
  if [ "$1" == "E" ]; then
    green  "empty    " 
  elif [ "$1" == "M" ]; then
    green  "all match" 
  elif [ "$1" == "F" ]; then
    green  "1st match" 
  elif [ "$1" == "L" ]; then
    yellow "1st lines"
  elif [ "$1" == "D" ]; then
    red    "different"
  else
    printf "         "
  fi
  printf "$2"
}

#
# $1: mode
# $2: infile
# $3: output status
# $4: error status
# $5: extra output status, or empty
# $6: extra error status, or empty
#
# All empty? Prints header line.
#
# stati:
#    M = matches perfectly
#    F = first error matches perfectly
#    L = line numbers match for first error
#    D = first errors are different
#
summaryLine()
{
  mode=$1
  infile=$2
  baout=$3
  baerr=$4
  exout=$5
  exerr=$6

  if [ $infile ]; then
    printf "%-4s %-25s     " $mode $infile
    showStatus $baout "  "
    showStatus $baerr "  "
    showStatus $exout "  "
    showStatus $exerr "\n"
  else
    printf -- "---- %-25s     ---------  ---------  ---------  ---------\n" "-------------------------"
    printf "%-4s %-25s     Basic Out  Basic Err  Extra Out  Extra Err\n" "Mode" "Test file"
    printf -- "---- %-25s     ---------  ---------  ---------  ---------\n" "-------------------------"
  fi
}

#############################################################

trap bailout INT

if [ $# -eq 0 ]; then
  usage 0
fi

STUB=`mktemp XXXXXX`

EXE=$1
shift

if [ ! -x $EXE ]; then
  echo "Can't execute $EXE"
  usage 1
fi

GENBASIC=""
GENEXTRA=""


echo Running tests using compiler:
./$EXE -0 | awk '{print "  | " $0}'

echo " "

TOnext=""
for arg; do

# check for options/switches

  if [ $TOnext ]; then
    TIMEOUT=$arg
    TOnext=""
    continue
  fi

  case "$arg" in
    -[1-5])
        MODE=$[ -arg ]
        continue
        ;;

    -d)
        SUMMARY=""
        echo "----------------------------------------------------------------------"
        continue
        ;;

    -gb)
        GENBASIC="y"
        continue
        ;;

    -ge)
        GENEXTRA="y"
        continue
        ;;

    -o)
        DASHO="y"
        continue
        ;;

    -s)
        SUMMARY="y"
        summaryLine
        continue
        ;;

    -t)
        TOnext="y"
        continue
        ;;

  esac


  EXOUT="$arg.extra.output$MODE"
  EXERR="$arg.extra.error$MODE"
  BAOUT="$arg.output$MODE"
  BAERR="$arg.error$MODE"

# are we generating outputs?

  if [ $GENBASIC ]; then
    echo generating regular outputs for $arg in mode $MODE
    ./$EXE -$MODE -o $BAOUT $arg 2> $BAERR
    checkDuplicate $BAOUT $EXOUT
    checkDuplicate $BAERR $EXERR
    continue
  fi

  if [ $GENEXTRA ]; then
    echo generating extra credit outputs for $arg in mode $MODE
    ./$EXE -$MODE -o $EXOUT $arg 2> $EXERR
    checkDuplicate $BAOUT $EXOUT
    checkDuplicate $BAERR $EXERR
    continue
  fi

# we're testing and comparing with output files.
# first, make sure expected output files are present.

  if [ ! -f $BAOUT ]; then
    continue
  fi

  if [ ! -f $BAERR ]; then
    continue
  fi

# Outputs are there.
# Run the compiler, with a timeout (in case it hangs)

  if [ ! $SUMMARY ]; then
    echo "$arg in mode $MODE"
  fi
  timeoutCompile $arg $STUB

#
# Get error/output stati
#

  STAT_BAOUT=`getOutStatus $BAOUT $STUB.output$MODE`
  STAT_EXOUT=`getOutStatus $EXOUT $STUB.output$MODE`

  STAT_BAERR=`getErrStatus $BAERR $STUB.error$MODE`
  STAT_EXERR=`getErrStatus $EXERR $STUB.error$MODE`

  if [ $SUMMARY ]; then
    summaryLine $MODE $arg $STAT_BAOUT $STAT_BAERR $STAT_EXOUT $STAT_EXERR
  else
    detailOut $STAT_BAOUT "Basic Output" $BAOUT $STUB.output$MODE
    detailErr $STAT_BAERR "Basic Error " $BAERR $STUB.error$MODE
    detailOut $STAT_EXOUT "Extra Credit Output" $EXOUT $STUB.output$MODE
    detailErr $STAT_EXERR "Extra Credit Error " $EXERR $STUB.error$MODE
  fi

  rm $STUB.output$MODE $STUB.error$MODE
done
cleanup


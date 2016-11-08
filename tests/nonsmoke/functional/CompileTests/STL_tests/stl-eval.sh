#!/bin/bash
# Author: Markus Schordan, 2016.

: ${TOOL1:=g++}
: ${TOOL2:=identityTranslator}

CLEANUP="yes"

if [ "$#" -gt 1 ]; then
    echo "Usage: $0 [no-cleanup]"
    exit
else
  if [ $# == 1 ]; then
    if [ "$1" == "no-cleanup" ]; then
      CLEANUP="no"
    else
      echo "Error: unknown argument $1."
      exit
    fi
  fi
fi

###############################################################################
# the following four lists control the behavior of the script
###############################################################################

STL_CPP98_HEADERS_PASSING="algorithm   deque exception functional limits list map memory new numeric queue set stack typeinfo utility valarray vector"
STL_CPP98_HEADERS_FAILING="bitset complex fstream iomanip ios iosfwd iostream istream iterator locale ostream sstream stdexcept streambuf string"

# C++11 TESTS are expected to pass for frontend (T0_FAIL+T1_FAIL==0 (but not for backend (T2_FAIL>0))
STL_CPP11_HEADERS_PASSING="algorithm bitset complex deque exception fstream functional iomanip ios iosfwd iostream istream iterator limits list locale map memory new numeric ostream queue set sstream stack stdexcept streambuf string typeinfo utility valarray vector"
STL_CPP11_HEADERS_FAILING=""

###############################################################################

GREEN="\033[32;0m"   # Green
RED="\033[31;1m"   # Red
COLOREND="\033[0m"
REDFAIL="${RED}FAIL${COLOREND}"

BS_INCLUDE=-I.
LOGFILE="stl-eval.log"
TOOL2_BACKEND=-rose:skipfinalCompileStep

function cleanup {
    rm -f $LOGFILE
    rm -f *.o *.pp.C *.ti
    rm -f test_*.* rose_test*.* a.out
}

function test_failed {
    echo -e "${RED}${TOTAL_FAIL} TESTS FAILED. See above list for details.${COLOREND}"
    exit 1
}

function check {

local STL_HEADERS=$1
local LANG_STANDARD=$2
local COMMENT=$3

T0_PASS=0
T0_FAIL=0
T1_PASS=0
T1_FAIL=0
T2_PASS=0
T2_FAIL=0
TOTAL_FAIL=0

for header in ${STL_HEADERS}; do

    TEST_HEADER="test_$header"
    TEST_HEADER_C="test_$header.C"
    # replace ++ in language standard by x to avoid problems with grep
    LANG_STANDARD_NO_PLUS=`echo $LANG_STANDARD | tr + x ` 
    TEST_HEADER_PP_C="${TEST_HEADER}_${LANG_STANDARD_NO_PLUS}.pp.C"
    ROSE_TEST_HEADER_PP_C="rose_${TEST_HEADER}_${LANG_STANDARD_NO_PLUS}.pp.C"
#    TEST_HEADER_FAIL1="${CPP_TEST_HEADER}_${LANG_STANDARD}.t1.fail.C"
#    TEST_HEADER_FAIL2="${CPP_TEST_HEADER}_${LANG_STANDARD}.t2.fail.C"

    printf "TESTING: %-17s: " "$header"
    printf "#include <$header>\nint main(){ return 0; }\n" > ${TEST_HEADER_C}
    # option -P: inhibit generation of linemarkers
    cpp -P -std=$LANG_STANDARD -x c++ ${TEST_HEADER_C} ${TEST_HEADER_PP_C}
    LOC=`wc -l ${TEST_HEADER_PP_C} | cut -f1 -d' '`
    printf "%6s LOC : " "$LOC"
    
    # use a sub shell and redirect coredump output of subshell to /dev/null
    {
        $TOOL1 $BS_INCLUDE ${TEST_HEADER_C} -std=$LANG_STANDARD &> /dev/null
    } > /dev/null 2>&1
    
    if [ $? -eq 0 ]; then
        echo -n "PASS " # 0
        ((T0_PASS+=1))
        echo "----------------------------------------------------------------------------------------------------------------" >> $LOGFILE
        echo "$TOOL2 $TOOL2_BACKEND $BS_INCLUDE ${TEST_HEADER_PP_C} -std=$LANG_STANDARD" >> $LOGFILE
        {
            $TOOL2 $TOOL2_BACKEND $BS_INCLUDE --edg:no_warnings ${TEST_HEADER_PP_C} -std=$LANG_STANDARD
        } >> $LOGFILE 2>&1
        if [ $? -eq 0 ]; then
            if [ -e ${ROSE_TEST_HEADER_PP_C} ]
            then
                echo -n "PASS" # 1
                ((T1_PASS+=1) )
                echo "${TOOL1} -std=$LANG_STANDARD ${ROSE_TEST_HEADER_PP_C} -w -Wfatal-errors" >> $LOGFILE
                ${TOOL1} -std=$LANG_STANDARD ${ROSE_TEST_HEADER_PP_C} -w -Wfatal-errors >> $LOGFILE 2>&1
                if [ $? -eq 0 ]; then
                    echo -n " PASS : 100.00%" # 2
                    ((T2_PASS+=1))
                else
                    # determine line number of error
                    ERROR_LINE=`${TOOL1} -std=${LANG_STANDARD} ${ROSE_TEST_HEADER_PP_C} -w -Wfatal-errors 2>&1 | egrep ${ROSE_TEST_HEADER_PP_C}:[0-9] | cut -f2 -d:` 
                    ERROR_PERCENTAGE=`echo "scale=2; ${ERROR_LINE}*100/${LOC}" | bc`
                    echo -en " ${RED}FAIL${COLOREND}"
                    printf " : %6s%% (LINE:%s)" "$ERROR_PERCENTAGE" "$ERROR_LINE" # 2
                    ((T2_FAIL+=1))
                    echo -n " [ ${TOOL1} -std=$LANG_STANDARD ${ROSE_TEST_HEADER_PP_C} -w -Wfatal-errors ]"
                fi            
            else
                echo -en " ${RED}FAIL${COLOREND} [no file generated!] "
                ((T1_FAIL+=1))
            fi
        else
            echo -en "${RED}FAIL ----${COLOREND}" # 1
            ((T1_FAIL+=1))
        fi
    else
        echo -en "${RED}FAIL ---- ----${COLOREND}" # 0
        ((T0_FAIL+=1))
        echo -n "[ $TOOL2 $TOOL2_BACKEND $BS_INCLUDE ${TEST_HEADER_PP_C} -std=$LANG_STANDARD ]"
    fi
    # print end of line with (optional) comment
    echo " $COMMENT"
    ((INDEX+=1))
done

if [ "x" == "x$1" ]; then
    echo "No passing tests."
else
    ((TOTAL_FAIL=T0_FAIL+T1_FAIL+T2_FAIL))
    # present statistics
    echo "-----------------------------------------------------------------"
    echo -e "PASS/FAIL                                $T0_PASS/${RED}$T0_FAIL${COLOREND} $T1_PASS/${RED}$T1_FAIL${COLOREND} $T2_PASS/${RED}$T2_FAIL${COLOREND} : TOTAL: ${T2_PASS}/${RED}${TOTAL_FAIL}${COLOREND}"
    echo "-----------------------------------------------------------------"
fi

} # end of function check

########################################################################

cleanup

echo
echo "-----------------------------------------------------------------"
echo "Testing with COMPILER (COMP): $TOOL1"
echo "             FRONTEND (FE)  : $TOOL2"
echo "             BACKEND (BE)   : $TOOL2"
echo "             TEST CLEANUP   : $CLEANUP"
echo "-----------------------------------------------------------------"
echo
echo "-----------------------------------------------------------------"
echo "STL C++98 FRONTEND+BACKEND CHECK         COMP FE   BE   : SUCCESS"
echo "-----------------------------------------------------------------"
# DQ: (comment out here to skip these tests).
check "$STL_CPP98_HEADERS_PASSING" "c++98" ""
if [ ${TOTAL_FAIL} -gt 0 ]; then
  test_failed
else
  echo "PASS (FRONTEND+BACKEND)."
fi

echo
echo "-----------------------------------------------------------------"
echo "STL C++98 FRONTEND+BACKEND CHECK         COMP FE   BE   : SUCCESS"
echo "-----------------------------------------------------------------"
# DQ: (comment out here to skip these tests).
check "$STL_CPP98_HEADERS_FAILING" "c++98" ""

# for headers known to fail, only the generated code fails (T2_FAIL)
# therefore we only check that the front end does not fail for any
# of those C++ 98 headers.
((CPP98_FAIL=T0_FAIL+T1_FAIL))
if [ ${CPP98_FAIL} -gt 0 ]; then
  test_failed
else
  echo "PASS (FRONTEND:PASS, BACKEND: known to fail)."
fi

echo
echo "-----------------------------------------------------------------"
echo "STL C++11 FRONTEND+BACKEND CHECK         COMP FE   BE   : SUCCESS"
echo "-----------------------------------------------------------------"
check "$STL_CPP11_HEADERS_PASSING" "c++11" ""

# code generation not correct for any C++11 header. We only check the front end.
((CPP11_FAIL=T0_FAIL+T1_FAIL))
if [ ${CPP11_FAIL} -gt 0 ]; then
  test_failed
else
  echo "PASS (FRONTEND:PASS, BACKEND: known to fail)."
fi

echo
echo -e "${GREEN}-----------------------------------------------------------------${COLOREND}"
echo -e "${GREEN}ALL TESTS PASSED (that are known to pass)${COLOREND}"
echo -e "${GREEN}-----------------------------------------------------------------${COLOREND}"

# clean up -- remove all generated files. cleanup is only performed when all tests passed and option "cleanup" is not provided to the script.
# for this option exists also a make target 'make check-no-cleanup'
if [ "$CLEANUP" == "yes" ]; then
  cleanup
fi

# NOTES on cpp:
# -fdirectives-only
#    When preprocessing, handle directives, but do not expand macros.
#    The option’s behavior depends on the -E and -fpreprocessed option

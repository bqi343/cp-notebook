# use this to grade your program given the input and output files

IN="I.#"
OUT="O.#"

TL=2
CPP="g++ -O2 -w -lm" # C++, -w = suppress warnings

red='\x1B[0;31m'
RED='\x1B[1;31m'
GREEN='\x1B[1;32m'
green='\x1B[0;32m'
blue='\x1B[0;34m'
BLUE='\x1B[1;34m'
cyan='\x1B[0;36m'
CYAN='\x1B[1;36m'
NC='\x1B[0m' # No Color

rm -f .overview .compiler_report .time_info .$1.out
trap "{ rm -f .overview .compiler_report .time_info .$1.out; }" SIGINT SIGTERM EXIT


if [ $# -ne 1 ]
then
	echo "Usage: $0 source_code"
	echo "   e.g. $0 test.cpp"
	echo "   use the above to grade file test.cpp"
	exit 2
fi

# Language detection
LANG=`echo $1 | awk -F . '{print $NF}'`
if [ "$LANG" == "cpp" ]
then
	COMPILER="$CPP $1 2> .compiler_report" # C++
fi

# Compilation
echo -e " ${CYAN}* Compiling source code${NC}";
echo "$COMPILER" | sh
if [ $? -ne 0 ]
then
	echo -e " ${RED}X Compilation Error${NC}";
	cat .compiler_report;
	exit 1;
fi

echo -e " ${GREEN}* Successful compilation!${NC}";
echo

ulimit -t $TL;

rm -rf .overview;
CORRECT=0
MAX_N=50

for (( i=1; i<=$MAX_N; i++))
do
	TEST_CASE_IN=`echo $IN | sed "s/#/$i/g"`
	TEST_CASE_OUT=`echo $OUT | sed "s/#/$i/g"`

	# If i-th test case doesn't exist then stop here.
	if [ ! -e $TEST_CASE_IN ]
	then
		break
	fi
	echo -e "${BLUE}Test case $i:${NC}";

	time -p (./a.out < $TEST_CASE_IN > .$1.out) 2> .time_info;

	EX_CODE=$?;
	if [ $EX_CODE -eq 152 ]
	then
		echo -e " ${RED}X TLE: Time Limit Exceeded${NC}";
		echo -n "T" >> .overview;
	elif [ $EX_CODE -ne 0 ]
	then
		echo -e " ${RED}X RE: Runtime Error${NC}";
		echo -n "E" >> .overview;
	else
		PROG_TIME=`cat .time_info | grep real | cut -d" " -f2`;
		diff --strip-trailing-cr .$1.out $TEST_CASE_OUT > /dev/null
		if [ $? -eq 0 ]
		then
			echo -e " ${GREEN}* OK${NC} [$PROG_TIME]"
			echo -n "*" >> .overview
			CORRECT=`expr $CORRECT + 1`
		else
			echo -e " ${RED}X WA: Wrong Answer${NC} [$PROG_TIME]"
			echo -n "X" >> .overview
		fi
	fi

	echo;
done
N=`expr $i - 1`

echo;

echo >> .overview;
echo -n "Overview: "; cat .overview
if [ $CORRECT -ne $N ]
then
	echo -e "${RED}X${NC}: Wrong Answer, ${RED}T${NC}: Time Limit Exceeded, ${RED}E${NC}: Probably runtime error"
	echo
fi

echo -n "$CORRECT / $N"
if [ $CORRECT -eq $N ]
then
	echo -en "   ${GREEN}AWWW YEAH :D${NC}"
fi
echo
#!/bin/bash

##
#Snippet from
#
#http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
#
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#
#end snippet
##

pushd ${SCRIPT_DIR}
make checker
popd

sh ${SCRIPT_DIR}/../scripts/compile_script.sh

pushd ${SCRIPT_DIR}

OUT=output.txt
RESULT=0

# Snippet from
# https://stackoverflow.com/a/169517

END=4
for f in $(seq 1 $END)
do
	ARGS=`cat testCases/test-${f}.txt`
	SOL=solutions/sol-${f}.txt

	echo "Running test ${f}"

	# You see this, and ask:
	# "You said not to use mpirun, what gives?"
	# This is because I can trust the tests that
	# I give to be small, and I don't trust students 
	# to run non-intensive tests on the login nodes, 
	# this is from experience that I saw firsthand
	mpirun -np $ARGS > $OUT
	./checker $SOL $OUT
	((RESULT|=$?))
done

echo 'Cleaning txts'
rm $OUT

echo 

if [[ $RESULT -eq 0 ]] 
then
	echo 'All tests passed'
else
	echo 'One or more tests failed'
fi

echo

popd

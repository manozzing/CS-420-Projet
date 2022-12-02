#!/bin/sh

##
#Snippet from
#
#http://stackoverflow.com/questions/59895/can-a-bash-script-tell-what-directory-its-stored-in
#
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#
#end snippet
##

pushd ${SCRIPT_DIR}/..

VERBOSE=1
if [ $# -eq 1 ]
  then
    VERBOSE=$1
fi

module load intel/18.0
module load gcc/7.2.0
module load cmake/3.18.4

mkdir -p build
pushd build
cmake -DCMAKE_C_FLAGS="-DVERBOSE_LEVEL=${VERBOSE}" ..
cmake --build .

popd
popd

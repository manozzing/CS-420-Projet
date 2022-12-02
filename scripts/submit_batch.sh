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

mkdir -p ${SCRIPT_DIR}/../batchFiles
mkdir -p ${SCRIPT_DIR}/../results

module load intel/18.0

JOB=`sbatch ${SCRIPT_DIR}/batch_script.run |cut -f 4 -d " "`
echo "Submitted batch job ${JOB}"

for NODES in 1 2 4 8 16
do
    sbatch --dependency=afterany:$JOB --nodes=$NODES --export=NODE_COUNT=$NODES ${SCRIPT_DIR}/batch_script4.run
done

popd

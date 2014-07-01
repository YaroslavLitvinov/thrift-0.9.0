#!/bin/bash
SAMPLES=/home/zvm/git/zerovm-samples
source $SAMPLES/run.env

$SAMPLES/ns_start.sh 2

${ZEROVM} TestServer.manifest &
${ZEROVM} TestClient.manifest 


for job in `jobs -p`
do
    wait $job
done

$SAMPLES/ns_stop.sh


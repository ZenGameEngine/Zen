#!/bin/sh

# Check if flamegraph-rs exists
fg=flamegraph 
if ! command -v $fg >/dev/null 2>&1
then
    echo "The command, $fg, was not found. Please install $fg-rs before running this script again."
    echo "The GitHub for $fg-rs is: https://github.com/flamegraph-rs/flamegraph"
    exit 1
fi

# Find out if Zenith exec exists
zenith=$(find "$(pwd)" -name "Zenith")
echo "Dir: ${zenith}"

if ! [ -f "$zenith" ]; then
echo "The Zenith Exec does not exist at the given directory, ${zenith}"
exit 1
else

"${zenith}" &
zenithPID=$(pidof Zenith)

flamegraph --output ZenithFlameGraph.svg --freq 200 --pid "${zenithPID}" &
sleep 30s
kill -15 "${zenithPID}"

fi 


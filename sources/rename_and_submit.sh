#!/bin/bash

PARAM_NAME="rrn_sm_36_m3"
TARGET="${PARAM_NAME}.out"
taskid=0

# Check if a.out exists, if so, rename it to xxx.out
if [ -f "./a.out" ]; then
    mv ./a.out "$TARGET"
    echo "Renamed a.out to $TARGET"
else
    echo "a.out not found. Please run make first."
    exit 1
fi

# If g2xxx.out file exists, run the program
if [ -f "$TARGET" ]; then
    nohup ./"$TARGET" "$taskid" > run.log 2>&1 &
    echo "$TARGET is running in the background"
else
    echo "$TARGET not found. Unable to run the program."
    exit 1
fi

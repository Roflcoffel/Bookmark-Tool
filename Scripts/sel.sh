#!/bin/bash

NUM=$1
isNumber='^[0-9]+$'

if ! [[ $NUM =~ $isNumber ]]
then
	echo "Error: Not a number"
	exit 1
fi

if ! [ $# -eq 1 ]
then
	echo "Error: To many arguments"
	exit 1
fi

curDIR=(*)
SIZE=${#curDIR[@]}

if [ $NUM -gt $SIZE ]
then
	echo "Error: Index do not exist"
	exit 1
fi

let NUM-- #Convert it to a 0 based index.
echo "${curDIR[$NUM]}"
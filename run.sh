#!/bin/bash
if [ "$#" -ne 1 ]; then
        echo "Illegal number of parameters"
        exit
fi
echo $1
if [ $1 -eq 2 ]
then (cd build; ./test)
elif [ $1 -eq 1 ]
then (cd build; ./assignment_O2)
fi

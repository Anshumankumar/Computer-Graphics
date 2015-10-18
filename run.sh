#!/bin/bash
if [ "$#" -ne 1 ]; then
        echo "Illegal number of parameters"
        exit
fi
echo $1
if [ $1 -eq 2 ]
then (cd build; ./test)
elif [ $1 -eq 1 ]
then (cd build; ./assignment_O3)
elif [ $1 -eq 3 ]
then (cd build; ./modelCreator)
elif [ $1 -eq 4 ]
then (cd build; ./createR2D2)


fi

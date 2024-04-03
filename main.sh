#!/bin/sh
unset _objects
unset objects
_objects=""
for file in libs/*.cpp 
    do filename=$(basename -- "$file")
    filename="${filename%.*}"
    _objects="${_objects}${filename}.o "
done
make main -e objects="${_objects}"

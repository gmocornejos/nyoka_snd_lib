#!/bin/bash

#To run this script you first need to give the file the correct permissions.
#chmod a+x compile.sh

cd src
echo "Compiling src"
make

cd ../examples
echo "Compiling examples"
make

echo "Done."

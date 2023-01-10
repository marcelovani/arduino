#!/bin/bash
clear

# Load includes
includes=$(cat main.ino | grep 'include.*\.cpp' | tr -d '"')

# Init build
echo > ./build/main.ino

for item in ${includes}
do
    if [[ "$item" == *".cpp"* ]]; then
        cat $item >> ./build/main.ino
        echo >> ./build/main.ino
    fi
done


cat main.ino | grep -v 'include "' >> ./build/main.ino

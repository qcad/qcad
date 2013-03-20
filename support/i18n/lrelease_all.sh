#!/bin/bash

cd ../..

# src:
for f in `find src -name "*.pro"`; do 
    echo $f
    lrelease $f
done

for f in `find scripts -name "*.pro"`; do 
    echo $f
    lrelease $f
done


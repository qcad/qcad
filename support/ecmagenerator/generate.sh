#!/bin/bash

if [ -z $1 ]; then
    maxThreads=64
else
    maxThreads=$1
fi

echo "Generating script bindings for the QCAD Application Framework..."

sh ./cpp2srcml.sh $maxThreads
if [ $? -ne 0 ]; then exit $?; fi
sh ./srcml2xml.sh $maxThreads
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2shell.sh $maxThreads
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2sharedpointersupport.sh $maxThreads
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2cpp.sh $maxThreads
if [ $? -ne 0 ]; then exit $?; fi

echo "done"

#!/bin/bash

if [ ! -z $1 ]; then
    scope="$1"
fi

echo "Generating script bindings for the QCAD Application Framework..."

sh ./cpp2srcml.sh $scope
if [ $? -ne 0 ]; then exit $?; fi
sh ./srcml2xml.sh $scope
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2shell.sh $scope
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2sharedpointersupport.sh $scope
if [ $? -ne 0 ]; then exit $?; fi
sh ./xml2cpp.sh $scope
if [ $? -ne 0 ]; then exit $?; fi

echo "done"

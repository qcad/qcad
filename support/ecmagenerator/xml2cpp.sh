#!/bin/bash

echo "xml to cpp..."

scope="src"
if [ -z $1 ]; then
    maxThreads=128
else
    maxThreads=$1
fi

hasNoIndent=0
which indent 1>/dev/null 2>&1
hasNoIndent=$?

if [ $scope == "src" ]; then
	profile="../../src/scripting/ecmaapi/ecmaapi.pro"
else
    profile="../../testing/scripting/ecmaapi/ecmaapi.pro"
fi

echo "include( ../../../shared.pri )" > "$profile"
echo "TEMPLATE = lib" >> "$profile"
echo "CONFIG += plugin" >> "$profile"
echo "TARGET = qcadecmaapi" >> "$profile"
echo "LIBS += -L$$PWD/$$ROUTDIR -ldxflib -lopennurbs -lqcadcore -lqcaddxf -lqcadentity -lqcadgrid -lqcadgui -lqcadoperations -lqcadsnap -lqcadspatialindex -lqcadstemmer -lspatialindexnavel -lstemmer" >> "$profile"
echo "CONFIG -= warn_on" >> $profile
echo "CONFIG += warn_off" >> $profile
echo "OTHER_FILES += ecmaapi.dox" >> $profile
if [ $scope == "src" ]; then
    echo "HEADERS += ../REcmaHelper.h" >> $profile
    echo "SOURCES += ../REcmaHelper.cpp" >> $profile
else
    echo "HEADERS += ../../../src/scripting/REcmaHelper.h" >> $profile
    echo "SOURCES += ../../../src/scripting/REcmaHelper.cpp" >> $profile
fi

threads=0
for f in `find $scope/xml -name "R[A-Z]*.xml" | sort` `find $scope/xml -name "Qt*.xml" | sort`
do
    for mode in h cpp
    do
        xmlfile=${f##*/}
        file=${xmlfile%%.*}
        if [[ $file == Qt* ]]; then
            ecmafile=$(echo $file|sed s/^Qt/QtEcma/).$mode
        else
            ecmafile=$(echo $file|sed s/^R/REcma/).$mode
        fi
        ecmapath=../../$scope/scripting/ecmaapi/$ecmafile

        echo "processing $file ($mode)"
        (
            xsltproc --stringparam scope $scope --stringparam mode $mode xml2cpp.xsl "$f" >"${ecmapath}_tmp"
            if [ -f $ecmapath ]; then
                diff $ecmapath ${ecmapath}_tmp
                if [ $? -eq 0 ]; then
                    rm ${ecmapath}_tmp
                else
                    mv ${ecmapath}_tmp $ecmapath
                fi
            else
                mv ${ecmapath}_tmp $ecmapath
            fi
        ) &
        let threads=threads+1
        if [ $threads -eq $maxThreads ]; then
            echo "waiting for threads to finish..."
            wait
            threads=0
        fi
    done
done

wait

for mode in h cpp
do
    for f in ../../$scope/scripting/ecmaapi/*.$mode
    do
        file=${f##*/}
        if [ -s $f ]; then
            if [ $mode == "h" ]; then

                echo "HEADERS += $file" >> "$profile"
            else
                echo "SOURCES += $file" >> "$profile"
            fi
        fi
    done
done

echo "done."

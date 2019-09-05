#!/bin/bash

echo "xml to cpp..."

maxThreads=1024
if [ -z $1 ]; then
    scope="src"
else
    scope="tmp"
fi

hasNoIndent=0
which indent 1>/dev/null 2>&1
hasNoIndent=$?

if [ $scope == "src" ]; then
    profile="../../src/scripting/ecmaapi/generated/generated.pri"
    profile_tmp="generated.pri"
fi

#echo "include( ../../../../shared.pri )" > "$profile_tmp"
#echo "TEMPLATE = lib" >> "$profile_tmp"
#echo "CONFIG += plugin" >> "$profile_tmp"
#echo "TARGET = qcadecmaapi" >> "$profile_tmp"
#echo "LIBS += -ldxflib -lopennurbs -lqcadcore -lqcaddxf -lqcadentity -lqcadgrid -lqcadgui -lqcadoperations -lqcadsnap -lqcadspatialindex -lqcadstemmer -lspatialindexnavel -lstemmer" >> "$profile_tmp"
#echo "CONFIG -= warn_on" >> $profile_tmp
#echo "CONFIG += warn_off" >> $profile_tmp
#echo "OTHER_FILES += ecmaapi.dox" >> $profile_tmp
#echo "DEFINES += QCADECMAAPI_LIBRARY" >> $profile_tmp
#for f in ../../$scope/scripting/ecmaapi/adapters/*.h
#do
#    bn=`basename $f`
#    echo "HEADERS += adapters/$bn" >> $profile_tmp
#done
#echo "SOURCES += adapters/RScriptAdapters.cpp" >> $profile_tmp
#if [ $scope == "src" ]; then
#    echo "HEADERS += ../REcmaHelper.h" >> $profile_tmp
#    echo "SOURCES += ../REcmaHelper.cpp" >> $profile_tmp
#else
#    echo "HEADERS += ../../../src/scripting/REcmaHelper.h" >> $profile_tmp
#    echo "SOURCES += ../../../src/scripting/REcmaHelper.cpp" >> $profile_tmp
#fi

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
        if [ $scope == "src" ]
        then
            ecmapath=../../$scope/scripting/ecmaapi/generated/$ecmafile
        else
            ecmapath=$1/$ecmafile
        fi

        echo "processing $file ($mode)"
        (
            xsltproc --stringparam scope $scope --stringparam mode $mode --stringparam cwd `pwd` xml2cpp.xsl "$f" >"${ecmapath}_tmp"
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

if [ $scope == "src" ]
then
    for mode in h cpp
    do
        if [ $mode == "h" ]; then
            /bin/echo -n "HEADERS +=" >> "$profile_tmp"
        else
            echo >> "$profile_tmp"
            /bin/echo -n "SOURCES +=" >> "$profile_tmp"
        fi

        for f in ../../$scope/scripting/ecmaapi/generated/*.$mode
        do
            file=${f##*/}
            if [ -s $f ]; then
                echo " \\" >> "$profile_tmp"
                /bin/echo -n "    \$\$PWD/$file" >> "$profile_tmp"
            fi
        done
    done

    cat $profile_tmp | grep -v "REcmaWebView" >tmp2
    mv tmp2 $profile_tmp
    echo "" >> "$profile_tmp"
    echo "contains(QT_VERSION, ^5\\.[1-5]\\..*) || contains(QT_VERSION, ^4\\..*\\..*) {" >> "$profile_tmp"
    echo "    !r_mobile {" >> "$profile_tmp"
    echo "        HEADERS += \$\$PWD/REcmaWebView.h" >> "$profile_tmp"
    echo "        SOURCES += \$\$PWD/REcmaWebView.cpp" >> "$profile_tmp"
    echo "    }" >> "$profile_tmp"
    echo "}" >> "$profile_tmp"

    diff $profile_tmp $profile
    if [ $? -eq 0 ]; then
        rm $profile_tmp
    else
        mv $profile_tmp $profile
    fi
fi

echo "done."

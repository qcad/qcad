#!/bin/bash
dirname=`dirname "$0"`
cd $dirname

tmp="tmp.qrc"

rm -rf allfiles.qrc

find ../../scripts -type f \( -name "*.js" -o -name "*.qm" -o -name "*.ui" -o -name "*.svg" -o -name "*.png" -o -name "*.jpg" -o -name "*.xsl" -o -name "*.ttf" -o -name "*.dxf" \) | /usr/bin/sort | sed "s#../../##" | sed "s#\(.*\)#    <file alias=\"\1\">../../\1</file>#" >>allfiles.qrc

find ../../ts -type f -name "*scripts_*.qm" \
    | /usr/bin/sort | sed "s#../../##" | sed "s#\(.*\)#    <file alias=\"\1\">../../\1</file>#" >>allfiles.qrc

#cat allfiles.qrc | grep -v "/actual/" | grep -v "/required/" | grep -v "/doc/" | sed s///g >${tmp}
cat allfiles.qrc | grep -v "/actual/" | grep -v "/doc/" | sed s///g >${tmp}
mv ${tmp} allfiles.qrc

for f in scripts scripts_release
do
    echo "<!DOCTYPE RCC><RCC version=\"1.0\">" > ${f}_new.qrc
    echo "  <qresource>" >> ${f}_new.qrc
    cat allfiles.qrc >> ${f}_new.qrc
    echo "  </qresource>" >> ${f}_new.qrc
    echo "</RCC>" >> ${f}_new.qrc

    if [ "$f" = "scripts_release" ]
    then
        cat ${f}_new.qrc | grep -v "/Developer/" | grep -v "/Tests/" | grep -v "/actual/" | grep -v "/required/" | grep -v ".dxf" >${tmp}
        mv ${tmp} ${f}_new.qrc
    fi

    #cat ${f}_new.qrc | grep -v "/QBook/" >${tmp}
    #mv ${tmp} ${f}_new.qrc

    diff ${f}.qrc ${f}_new.qrc
    if [ ! $? -eq 0 ]
    then
        mv ${f}_new.qrc ${f}.qrc
    else
        rm ${f}_new.qrc
    fi
done

rm -rf allfiles.qrc

qmake

#!/bin/bash
dirname=`dirname "$0"`
cd $dirname
CWD=`pwd`

fn="scripts"

echo "<!DOCTYPE RCC><RCC version=\"1.0\">" > ${fn}_new.qrc
echo "  <qresource>" >> ${fn}_new.qrc

for ext in js qm ui svg png
do
    files=`/usr/bin/find ../../res/scripts -name "*.$ext" | /usr/bin/sort`

    for f in $files
    do
        f2=`echo $f | sed s#../../res/##`
        echo "    <file alias=\"$f2\">$f</file>" >> ${fn}_new.qrc
    done
done


echo "  </qresource>" >> ${fn}_new.qrc
echo "</RCC>" >> ${fn}_new.qrc

cat ${fn}_new.qrc | grep -v "/Developer/" | grep -v "/Tests/" >tmp
mv tmp ${fn}_new.qrc

cat ${fn}_new.qrc | sed s///g >tmp
mv tmp ${fn}_new.qrc

diff ${fn}.qrc ${fn}_new.qrc
if [ ! $? -eq 0 ]
then
    mv ${fn}_new.qrc ${fn}.qrc
    # run qmake to update dependencies:
    qmake
else
    rm ${fn}_new.qrc
fi


#!/bin/bash
dirname=`dirname "$0"`
cd $dirname

echo "<!DOCTYPE RCC><RCC version=\"1.0\">" > scripts_new.qrc
echo "  <qresource>" >> scripts_new.qrc

for ext in js qm ui svg png
do
    for f in `/usr/bin/find ../../scripts -name "*.$ext" | grep -v "/Tests/" | /usr/bin/sort`
    do
        f2=`echo $f | sed s#../../##`
        echo "    <file alias=\"$f2\">$f</file>" >> scripts_new.qrc
    done
done


echo "  </qresource>" >> scripts_new.qrc
echo "</RCC>" >> scripts_new.qrc

diff scripts.qrc scripts_new.qrc
if [ ! $? -eq 0 ]
then
    mv scripts_new.qrc scripts.qrc
    # run qmake to update dependencies:
    qmake
else
    rm scripts_new.qrc
fi

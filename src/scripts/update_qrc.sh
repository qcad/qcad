#!/bin/bash
dirname=`dirname "$0"`
cd $dirname

sh ./gen_qrc.sh Release &

sleep 1

# development version:
sh ./gen_qrc.sh &

wait

# run qmake to update dependencies:
qmake

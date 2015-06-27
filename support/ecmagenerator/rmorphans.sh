#!/bin/bash

if [ $(uname) = "Darwin" ]; then
    exit 2
fi

if [ $# -lt 4 ]; then
    echo "Usage: $0 srcpath srcext dstpath dstext [prefix]"
    echo "eg.: $0 ../../src h srcml srcml [Ecma]"
    exit 1
fi

srcpath=$1
srcext=$2
dstpath=$3
dstext=$4
prefix=$5

find "$srcpath" -name "*.$srcext" -printf "%f\n" > "$TMPDIR/srclist.tmp"
find "$dstpath" -name "*.$dstext" -printf "%f\n" | sed "s/^R$prefix/R/" > "$TMPDIR/dstlist.tmp"

for f in "$TMPDIR/srclist.tmp" "$TMPDIR/dstlist.tmp"; do
    cat $f | sed "s/\..*$//" | sort > ${f}2
done

for f in $(diff --suppress-common-lines $TMPDIR/srclist.tmp2 $TMPDIR/dstlist.tmp2 | grep ">" | sed "s/> //"); do
    file=$(echo "$f" | sed "s/^R/R$prefix/")
    echo "removing $dstpath/$file.$dstext ..."
    rm -v "$dstpath/$file.$dstext"
done

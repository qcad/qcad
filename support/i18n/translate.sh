#!/bin/bash

lang="$1"
lang2="$2"
lang3="$3"
lang4="$4"
lang5="$5"
lang6="$6"

cd ../..
c=0
for f in `find ts -name "*_$lang.ts"` `find scripts -name "*_$lang.ts"`; do 
    let c=c+1

    echo $f

    # ignore:
    #if [[ $f == *Developer* ]]
    #then
    #    continue;
    #fi
    if [[ $f == *script_* ]]
    then
        continue;
    fi

    # additional languages:
    if [ ! -z "$lang2" ]
    then
        f2=`echo "$f" | sed s/_$lang./_$lang2./`
    fi
    if [ ! -z "$lang3" ]
    then
        f3=`echo "$f" | sed s/_$lang./_$lang3./`
    fi
    if [ ! -z "$lang4" ]
    then
        f4=`echo "$f" | sed s/_$lang./_$lang4./`
    fi
    if [ ! -z "$lang5" ]
    then
        f5=`echo "$f" | sed s/_$lang./_$lang5./`
    fi
    if [ ! -z "$lang6" ]
    then
        f6=`echo "$f" | sed s/_$lang./_$lang6./`
    fi

    if grep -q unfinished $f $f2 $f3 $f4 $f5 $f6
    then
        #echo "Updating dictionaries..."
        #cd support/i18n

        #if [ ! -z "$lang" ]
        #then
        #    sh ./autotranslate.sh $lang
        #fi
        #if [ ! -z "$lang2" ]
        #then
        #    sh ./autotranslate.sh $lang2
        #fi
        #if [ ! -z "$lang3" ]
        #then
        #    sh ./autotranslate.sh $lang3
        #fi
        #if [ ! -z "$lang4" ]
        #then
        #    sh ./autotranslate.sh $lang4
        #fi
        #if [ ! -z "$lang5" ]
        #then
        #    sh ./autotranslate.sh $lang5
        #fi
        #cd ../..

        echo "Translating $f $f2 $f3 $f4 $f5 $f6 [$c]..."
        ~/opt/qt/bin/Linguist.app/Contents/MacOS/Linguist $f $f2 $f3 $f4 $f5 $f6

    else
        echo "All done in $f [$c]..."
    fi
done

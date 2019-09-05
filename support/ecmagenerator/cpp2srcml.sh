#!/bin/bash

echo "cpp to srcml..."

if command -v src2srcml &>/dev/null
then
    echo "src2srcml found."
else
    echo "src2srcml not found. Skipping srcml generation..."
    exit 0
fi

maxThreads=1024

src2srcml_output=`src2srcml -h | grep \\\-\\\-output`

SPATH=$(pwd)
if [ -z "$1" ]
then
    scope="src"
    cd "../../$scope"
else
    scope="$1"
    find tmp -name "*.xml" | xargs rm
    find tmp -name "*.srcml" | xargs rm
    cd "$scope"
fi

# find out where srcml is located:
srcmlpath=`which srcml`
srcmlpath=`dirname "$srcmlpath"`

for f in `find . -name "R[A-Z]*.h"`
do
    # ignore 3rd party library code:
    if [[ $f == *3rdparty/* ]]; then continue; fi

    cppfile=${f##*/}
    if [ ${cppfile:0:5} != "REcma" ]; then
        basename=${cppfile%%.*}
        if [ $scope = "src" ]
        then
            srcmlfile="$scope/srcml/$basename.srcml"
        else
            srcmlfile="tmp/srcml/$basename.srcml"
        fi
        #if [ $f -nt "$SPATH/$srcmlfile" ]; then
            echo "processing $cppfile ..."
            #(
                src2srcml "$f" "$SPATH/$srcmlfile"
                #src2srcml "$f" -o "$SPATH/$srcmlfile"
                #if [ `uname` == "Darwin" ]
                #then
                #    DYLD_LIBRARY_PATH=$srcmlpath srcml "$f" -o "$SPATH/$srcmlfile"
                #else
                #    LD_LIBRARY_PATH=$srcmlpath srcml "$f" -o "$SPATH/$srcmlfile"
                #fi
                #tidy -q -i -xml -m "$SPATH/$srcmlfile" # tidy messes up things
            #) &
        #fi

        let threads=threads+1
        if [ $threads -eq $maxThreads ]; then
            echo "waiting for threads to finish..."
            sleep 0.1
            wait
            threads=0
        fi
    fi
done

cd $SPATH

wait

#./rmorphans.sh ../../$scope h $scope/srcml srcml

echo "done."

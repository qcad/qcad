#!/bin/bash

echo "cpp to srcml..."

if command -v src2srcml &>/dev/null
then
	echo "src2srcml found."
else
	echo "src2srcml not found. Skipping srcml generation..."
	exit 0
fi

maxThreads=256

src2srcml_output=`src2srcml -h | grep \\\-\\\-output`

# detect if src2srcml requires -o switch for output:
if [ "x$src2srcml_output" = "x" ]; then
    switch=""
else
    switch="-o"
fi

echo $switch

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
			(
				#src2srcml "$f" $switch "$SPATH/$srcmlfile"
				DYLD_LIBRARY_PATH=~/bin ~/bin/srcml "$f" $switch "$SPATH/$srcmlfile"
				#tidy -q -i -xml -m "$SPATH/$srcmlfile" # tidy messes up things
			) &
		#fi

        let threads=threads+1
        if [ $threads -eq $maxThreads ]; then
            echo "waiting for threads to finish..."
            wait
            threads=0
        fi
	fi
done

cd $SPATH

wait

#./rmorphans.sh ../../$scope h $scope/srcml srcml

echo "done."

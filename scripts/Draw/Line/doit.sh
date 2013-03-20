for f in `find . -name "*.js"`
do
    echo $f
    init=${f%.*}Init.js
    cp $f $init
done

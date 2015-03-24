for d in `find . -name "Tests"`
do
    echo $d
    for f in `find "$d" -name "*.js"`
    do
        echo $f
        cat $f | sed "s/::ModifyMenuButton/::ModifyToolsPanelButton/g" >tmp
        diff $f tmp
        if [ $? -eq 1 ]
        then
            mv tmp $f
        fi
    done
done

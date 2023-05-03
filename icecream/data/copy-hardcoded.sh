for i in {1..5}; do
    for f in sub$i_*/*.in; do
        g=sub$i-$(basename $f)
        cp $f $g
        echo $g
    done
done

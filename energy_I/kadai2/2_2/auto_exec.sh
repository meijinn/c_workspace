#!/usr/bin/env bash
i=1000
while [ "$i" -le 100000 ];
do
    g++ sample1-4.cpp -o a.out
    ./a.out

    sed -i -e '1,2d' "kadai2_$i.csv"

    j=$(expr "$i")
    i=$(expr "$i" + 1000)
    sed -i -e "9s/kadai2_$j.csv/kadai2_$i.csv/" ./parameter.inc
    sed -i -e "17s/$j/$i/" ./parameter.inc
done

mv kadai2_*.csv warm_result
zip warm_result -r warm_result
rm -rf kadai2_*.-e
echo $(exit)

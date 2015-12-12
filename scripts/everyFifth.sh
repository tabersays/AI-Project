#!/usr/bin/env bash
# @author Taber Storm Fitzgerald
COUNT=0;
for i in *.png;
do
    if ((COUNT%5 == 0)); then
            cp $i ../test/$i;
            rm $i;
    fi
        ((COUNT++));
done

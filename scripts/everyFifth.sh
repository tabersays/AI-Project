#!/usr/bin/env bash

COUNT=0;
for i in *.png;
do
    if ((COUNT%5 == 0)); then
            cp $i ../test/$i;
            rm $i;
    fi
        ((COUNT++));
done
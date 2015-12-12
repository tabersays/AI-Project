#!/usr/bin/env bash
# @author Taber Storm Fitzgerald
#This script flattens the png's then converts them to bmp's and moves them into the bmp directory.
#This assumes it is going to be run from the /dataSet/png directory
for i in *.png;
    do 
        convert -flatten $i $i;
        convert -monochrome -depth 1 $i ${i/.png}.bmp;
    done
for i in *.bmp;
    do
        cp $i ../bmp/;
        rm $i;
    done

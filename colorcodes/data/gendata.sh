#!/bin/bash

python gendata.py

for f in secret/*in; do
    time pypy ../submissions/accepted/colourcodes.py < $f > ${f%.in}.ans
done

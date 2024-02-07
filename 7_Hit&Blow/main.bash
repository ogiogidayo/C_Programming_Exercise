#! /bin/bash
for i in {1..100}; do
    formatted_number=$(printf "%03d" $i)
    ./main "hist${formatted_number}.txt"
done
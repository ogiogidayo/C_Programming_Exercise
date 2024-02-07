#!/bin/bash

output="scores.csv"
if [ -f "$output" ]; then
    rm "$output"
fi

for i in $(seq 1 100); do
    file=$(printf "hist%03d.txt" $i)
    score=$(tail -n 1 "$file" | awk '{print $2}')
    echo "$i, $score" >> "$output"
done
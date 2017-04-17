#!/bin/bash

while [ 1 == 1 ]
do
read files

./bin/zcc res/myc_grammar.txt res/parsing_table.txt $files
echo "---------------------------------"
echo ""
done
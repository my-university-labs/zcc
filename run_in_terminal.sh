#!/bin/bash
read files

./bin/zcc res/myc_grammar.txt res/parsing_table.txt $files

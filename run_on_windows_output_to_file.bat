@echo off

set lib_loc=%cd%\lib

set PATH=%lib_loc%;

echo input test-file-name please

echo file is %xxxx%

.\bin\zcc.exe res/myc_grammar.txt res/parsing_table.txt  %xxxx% > result.txt

echo DONE see result.txt

echo. &pause    
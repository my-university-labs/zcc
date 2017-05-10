@echo off

set lib_loc=%cd%\lib

set PATH=%lib_loc%;

echo input test-file-name please

set/p xxxx= >nul

.\bin\zcc.exe res/myc_grammar.txt res/parsing_table.txt %xxxx%

echo. &pause    
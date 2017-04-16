@echo off

echo input test-file-name

set/p xxxx= >nul

echo file is %xxxx%

.\bin\zcc.exe res/myc_grammar.txt res/parsing_table.txt %xxxx%

echo. &pause    
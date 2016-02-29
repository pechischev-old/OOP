rem @echo off
SET program="%1"
if %program% == "" goto err

%program% input.txt output1.txt "" REPLACE > out.txt
IF ERRORLEVEL 1 GOTO testFailed
fc.exe output1.txt checkOutput/emptySearch.txt
IF ERRORLEVEL 1 GOTO testFailed

%program% TrueInput.txt output3.txt ma mama > out2.txt
IF ERRORLEVEL 1 GOTO testFailed
fc.exe output3.txt checkOutput/mama.txt
if ERRORLEVEL 1 goto testFailed

%program% input.txt output2.txt 1231234 true > out3.txt
IF ERRORLEVEL 1 GOTO testFailed
fc.exe output2.txt checkOutput/1231234.txt
if ERRORLEVEL 1 goto testFailed

%program% empty.docx output4.txt 1231234 true > out4.txt
IF ERRORLEVEL 1 GOTO testFailed
fc.exe output4.txt checkOutput/empty.txt
if ERRORLEVEL 1 goto testFailed

echo OK
EXIT /B

:testFailed
ECHO Testing failed
exit /b

:err
echo Usage: test.bat <Path to program>
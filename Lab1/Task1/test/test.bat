echo off

Task1.exe 
IF NOT ERRORLEVEL 1 GOTO err

echo empty search string
Task1.exe input.txt output1.txt "" REPLACE 
IF ERRORLEVEL 1 GOTO testFailed
fc /b output1.txt checkOutput/emptySearch.txt
IF ERRORLEVEL 1 GOTO testFailed

echo replace ma on mama
Task1.exe TrueInput.txt output3.txt ma mama 
IF ERRORLEVEL 1 GOTO testFailed
fc /b output3.txt checkOutput/mama.txt
if ERRORLEVEL 1 goto testFailed

echo replace 1231234
Task1.exe input.txt output2.txt 1231234 true 
IF ERRORLEVEL 1 GOTO testFailed
fc /b output2.txt checkOutput/1231234.txt
if ERRORLEVEL 1 goto testFailed

echo replace in empty file
Task1.exe empty.docx output4.txt 1231234 true 
IF ERRORLEVEL 1 GOTO testFailed
fc /b output4.txt checkOutput/empty.txt
if ERRORLEVEL 1 goto testFailed

echo OK
EXIT /B

:testFailed
ECHO Testing failed
exit /b

:err
echo Usage: invalid characters
rem @echo off
SET program="%1"
if %program% == "" goto err

echo check on empty file
%program% empty.txt outEmpty.txt
if errorlevel 1 goto testFailed
fc /b outEmpty.txt check/empty.txt
if errorlevel 1 goto testFailed

echo to fill normal file
%program% fill.txt outFill.txt
if errorlevel 1 goto testFailed
fc /b outFill.txt check/fill-2.txt
if errorlevel 1 goto testFailed

echo check invalid symbol
%program% invalidSymbol.txt outInvalid.txt > outInvalid.txt
if errorlevel 1 goto testFailed
fc /b outInvalid.txt check/invalid.txt
if errorlevel 1 goto testFailed

echo fill with one point
%program% fillWithOnePoint.txt outOnePoint.txt
if errorlevel 1 goto testFailed
fc /b outOnePoint.txt check/one_point.txt
if errorlevel 1 goto testFailed

echo fill big array
%program% ecross.txt outEcross.txt
if errorlevel 1 goto testFailed
fc /b outEcross.txt check/ecross.txt
if errorlevel 1 goto testFailed

echo OK
exit /b

:testFailed
echo Testing failed
exit /b


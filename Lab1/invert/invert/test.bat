rem @echo off
SET program="%1"
if %program% == "" goto err

echo invert matrix at determinate = 0
%program% Det0.txt > outDet0.txt
if errorlevel 1 goto testFailed
fc /b outDet0.txt check/no_invert.txt
if errorlevel 1 goto testFailed

echo invert matrix with int value
%program% int.txt > outInt.txt
if errorlevel 1 goto testFailed
fc /b outInt.txt check/int.txt
if errorlevel 1 goto testFailed

echo invert matrix with float value
%program% float.txt > outFloat.txt
if errorlevel 1 goto testFailed
fc /b outFloat.txt check/float.txt
if errorlevel 1 goto testFailed

echo open empty file
%program% empty.txt > outEmpty.txt
if not errorlevel 1 goto testFailed
fc /b outEmpty.txt check/size.txt
if errorlevel 1 goto testFailed

echo invert matrix with different values
%program% matrix.txt > outMatrix.txt
if errorlevel 1 goto testFailed
fc /b outMatrix.txt check/matrix.txt
if errorlevel 1 goto testFailed

echo matrix with symbol 
%program% symbol.txt > outSymbol.txt
if not errorlevel 1 goto testFailed
fc /b outSymbol.txt check/symbol.txt
if errorlevel 1 goto testFailed

echo file size exceeds
%program% wrongSize.txt > outSize.txt
if not errorlevel 1 goto testFailed
fc /b outSize.txt check/size.txt
if errorlevel 1 goto testFailed


echo OK
exit /b

:testFailed
echo Testing failed
exit /b

:err
echo Usage: test.bat <Path to program>

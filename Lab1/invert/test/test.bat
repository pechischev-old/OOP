echo off

echo invert matrix at determinate = 0
invert.exe Det0.txt > outDet0.txt
if errorlevel 1 goto testFailed
fc /b outDet0.txt check/no_invert.txt
if errorlevel 1 goto testFailed

echo invert matrix with int value
invert.exe int.txt > outInt.txt
if errorlevel 1 goto testFailed
fc /b outInt.txt check/int.txt
if errorlevel 1 goto testFailed

echo invert matrix with float value
invert.exe float.txt > outFloat.txt
if errorlevel 1 goto testFailed
fc /b outFloat.txt check/float.txt
if errorlevel 1 goto testFailed

echo open empty file
invert.exe empty.txt > outEmpty.txt
if errorlevel 1 goto testFailed
fc /b outEmpty.txt check/size.txt
if errorlevel 1 goto testFailed

echo invert matrix with different values
invert.exe matrix.txt > outMatrix.txt
if errorlevel 1 goto testFailed
fc /b outMatrix.txt check/matrix.txt
if errorlevel 1 goto testFailed

echo matrix with symbol 
invert.exe symbol.txt > outSymbol.txt
if errorlevel 1 goto testFailed
fc /b outSymbol.txt check/symbol.txt
if errorlevel 1 goto testFailed

echo file size exceeds
invert.exe wrongSize.txt > outSize.txt
if errorlevel 1 goto testFailed
fc /b outSize.txt check/size.txt
if errorlevel 1 goto testFailed


echo OK
exit /b

:testFailed
echo Testing failed
exit /b

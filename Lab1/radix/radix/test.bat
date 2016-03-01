rem @echo off
SET program="%1"
if %program% == "" goto err

echo translate from 16 to 10 value 1f
%program% 16 10 1f > 1f.txt
if errorlevel 1 goto testFailed
fc /b 1f.txt check/1f_16_10.txt
if errorlevel 1 goto testFailed

echo translate from 15 to 3 value 34ab3
%program% 15 3 34ab3 > 34ab3_15_3.txt
if errorlevel 1 goto testFailed
fc /b 34ab3_15_3.txt check/34ab3_15_3.txt
if errorlevel 1 goto testFailed

echo translate from 25 to 5 value -456
%program% 25 5 -456 > -456_25_5.txt
if errorlevel 1 goto testFailed
fc /b -456_25_5.txt check/-456_25_5.txt
if errorlevel 1 goto testFailed

echo translate from 9 to 8 value 789
%program% 9 8 789 > 789_9_8.txt
if errorlevel 1 goto testFailed
fc /b 789_9_8.txt check/exceeds.txt
if errorlevel 1 goto testFailed

echo translate from 16 to 2 value GGG
%program% 16 2 GGG > GGG_16_2.txt
if errorlevel 1 goto testFailed
fc /b GGG_16_2.txt check/exceeds.txt
if errorlevel 1 goto testFailed

echo translate from 36 to 1 value 435345353
%program% 36 1 435345353 > 435345353_36_1.txt
if not errorlevel 1 goto testFailed
fc /b 435345353_36_1.txt check/disparity.txt
if errorlevel 1 goto testFailed

echo translate from 37 to 10 value RRR
%program% 37 10 RRR > RRR_37_10.txt
if not errorlevel 1 goto testFailed
fc /b RRR_37_10.txt check/disparity.txt
if errorlevel 1 goto testFailed

echo translate from 16 to 10 value 0
%program% 16 10 0 > 0_16_10.txt
if errorlevel 1 goto testFailed
fc /b 0_16_10.txt check/0_16_10.txt
if errorlevel 1 goto testFailed

echo translate from 10 to 16 value 2147483647
%program% 10 16 2147483647 > 2147483647_10_16.txt
if errorlevel 1 goto testFailed
fc /b 2147483647_10_16.txt check/2147483647_10_16.txt
if errorlevel 1 goto testFailed


echo OK
exit /b

:testFailed
ECHO Testing failed
exit /b

:err
echo Usage: test.bat <Path to program>
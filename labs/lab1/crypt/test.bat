set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

rem %PROGRAM% > nul
rem if NOT ERRORLEVEL 1 goto err

rem simple test
%PROGRAM% crypt input1_plain.txt output1_crypt.txt 128

%PROGRAM% decrypt output1_crypt.txt output1_decrypt.txt 128

rem test key is min
%PROGRAM% crypt input1_plain.txt output1_crypt.txt 0

%PROGRAM% decrypt output1_crypt.txt output1_decrypt.txt 0

rem test key is max
%PROGRAM% crypt input1_plain.txt output1_crypt.txt 255

%PROGRAM% decrypt output1_crypt.txt output1_decrypt.txt 255

rem test %POROGRAM% mode isn't correct spelled
%PROGRAM% 1crypt input1_plain.txt output1_crypt.txt 0
%PROGRAM% decrypt2 output1_crypt.txt output1_decrypt.txt 0
rem test <input file> err
%PROGRAM% decrypt some_not_exist.txt output1_decrypt.txt 0
rem test <output file> err
%PROGRAM% decrypt input1_plain.txt some_not_exist.txt 0
rem test <key> err 0 <= <key> <= 255
%PROGRAM% decrypt input1_plain.txt some_not_exist.txt -1
%PROGRAM% decrypt input1_plain.txt some_not_exist.txt 256

%PROGRAM% "" "" "" ""
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
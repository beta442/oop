set PROGRAM="%~1"
set DIR=%TEMP%
set TEMP_TXT="temp_output.txt"

echo "" > %TEMP_TXT%

rem simple test
%PROGRAM% crypt input_plain_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% output_crypt_128.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

%PROGRAM% decrypt output_crypt_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% output_decrypt_128.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem test key is min
%PROGRAM% crypt input_plain_0.txt %TEMP_TXT% 0
fc.exe %TEMP_TXT% output_crypt_0.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

%PROGRAM% decrypt output_crypt_0.txt %TEMP_TXT% 0
fc.exe %TEMP_TXT% output_decrypt_0.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem test key is max
%PROGRAM% crypt input_plain_255.txt %TEMP_TXT% 255
fc.exe %TEMP_TXT% output_crypt_255.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

%PROGRAM% decrypt output_crypt_255.txt %TEMP_TXT% 255
fc.exe %TEMP_TXT% output_decrypt_255.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem png crypt test
%PROGRAM% crypt png_test.png %TEMP_TXT% 128
fc.exe %TEMP_TXT% png_out_crypt_128.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

%PROGRAM% decrypt png_out_crypt_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% png_out_decrpyt_128.png
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem test %POROGRAM% mode isn't correct spelled
%PROGRAM% 1crypt input_plain_0.txt output_crypt_0.txt 0
%PROGRAM% decrypt2 output_crypt_0.txt output_decrypt_0.txt 0
rem test <input file> err
%PROGRAM% decrypt some_not_exist.txt output_decrypt_0.txt 0
rem test <output file> err
%PROGRAM% decrypt input_plain_0.txt some_not_exist.txt 0
rem test <key> err 0 <= <key> <= 255
%PROGRAM% decrypt input_plain_0.txt output_decrypt_0.txt -1
%PROGRAM% decrypt input_plain_0.txt output_decrypt_0.txt 256
%PROGRAM% "" "" "" ""
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

echo OK
exit 0

:err
echo Program testing failed
exit 1
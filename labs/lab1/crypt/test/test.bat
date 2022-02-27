set PROGRAM="%~1"
set DIR=%TEMP%
set TEMP_TXT="%DIR%\\temp.txt"

del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem simple test
%PROGRAM% crypt input_plain_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% output_crypt_128.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% decrypt output_crypt_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% output_decrypt_128.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem test key is min
%PROGRAM% crypt input_plain_0.txt %TEMP_TXT% 0
fc.exe %TEMP_TXT% output_crypt_0.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% decrypt output_crypt_0.txt %TEMP_TXT% 0
fc.exe %TEMP_TXT% output_decrypt_0.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem test key is max
%PROGRAM% crypt input_plain_255.txt %TEMP_TXT% 255
fc.exe %TEMP_TXT% output_crypt_255.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% decrypt output_crypt_255.txt %TEMP_TXT% 255
fc.exe %TEMP_TXT% output_decrypt_255.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem png crypt test
%PROGRAM% crypt png_test.png %TEMP_TXT% 128
fc.exe %TEMP_TXT% png_out_crypt_128.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% decrypt png_out_crypt_128.txt %TEMP_TXT% 128
fc.exe %TEMP_TXT% png_out_decrpyt_128.png
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem err_tests

rem test %POROGRAM% mode isn't correct spelled
%PROGRAM% 1crypt input_plain_0.txt output_crypt_0.txt 0 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_invalid_program_mode.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% decrypt2 output_crypt_0.txt output_decrypt_0.txt 0 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_invalid_program_mode.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem test <input file> err
%PROGRAM% decrypt some_not_exist.txt output_decrypt_0.txt 0 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_input_not_exists.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5
rem test <output file> err
%PROGRAM% decrypt input_plain_0.txt some_not_exist.txt 0 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_output_not_exists.txt
del %TEMP_TXT%
echo "" > %TEMP_TXT%
if ERRORLEVEL 1 goto err
timeout /t 5

rem test <key> err 0 <= <key> <= 255
%PROGRAM% decrypt input_plain_0.txt output_decrypt_0.txt -1 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_wrong_key_value.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5
%PROGRAM% decrypt input_plain_0.txt output_decrypt_0.txt 256 > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_wrong_key_value.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

rem empty args
%PROGRAM% "" "" "" "" > %TEMP_TXT%
fc.exe %TEMP_TXT% err_tests\\output_err_empty_args.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

echo OK
exit 0

:err
echo Program testing failed
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5
exit 1
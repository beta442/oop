set PROGRAM="%~1"
set DIR=%TEMP%
set TEMP_TXT="%DIR%\\temp.txt"
set ERR_TESTS_DIR="err_tests"

del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem correct tests
%PROGRAM% input_default.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_default.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_default_invert.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_default_invert.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_100_100.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_100_100.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_large.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_large.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_over_100_100.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_over_100_100.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_over_100_100_invert.txt %TEMP_TXT%
fc.exe %TEMP_TXT% output_over_100_100_invert.txt
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

err params
%PROGRAM% asdsa sadsad > %TEMP_TXT%
fc.exe %TEMP_TXT% "%ERR_TESTS_DIR%\\output_err_empty_input_file.txt"
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% input_empty.txt output1.txt > %TEMP_TXT%
fc.exe %TEMP_TXT% "%ERR_TESTS_DIR%\\output_err_empty_input_file.txt"
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% "" "" > %TEMP_TXT%
fc.exe %TEMP_TXT% "%ERR_TESTS_DIR%\\output_err_empty_args.txt"
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

%PROGRAM% "" "" ""> %TEMP_TXT%
fc.exe %TEMP_TXT% "%ERR_TESTS_DIR%\\output_err_args_amount.txt"
if ERRORLEVEL 1 goto err
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5

del %TEMP_TXT%
echo "" > %TEMP_TXT%
echo OK
timeout /t 5
exit 0

:err
echo Program testing failed
del %TEMP_TXT%
echo "" > %TEMP_TXT%
timeout /t 5
exit 1
set PROGRAM="%~1"
set DIR=%TEMP%

rem simple tests
%PROGRAM% 16 22 ABDCEF > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_16_to_22.txt
if ERRORLEVEL 1 goto err
timeout /t 5

rem from biggest notation to smallest
%PROGRAM% 36 2 ZZZZ > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_36_to_2.txt
if ERRORLEVEL 1 goto err
timeout /t 5
rem reverse
%PROGRAM% 2 36 110011010000011111111 > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_2_to_36.txt
if ERRORLEVEL 1 goto err
timeout /t 5

rem err tests

rem too large values
%PROGRAM% 16 10 FFFFFFFF > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_too_large_value.txt
if ERRORLEVEL 1 goto err
timeout /t 5
%PROGRAM% 16 10 -FFFFFFFF > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_too_large_value.txt
if ERRORLEVEL 1 goto err
timeout /t 5

rem err params
%PROGRAM% 0 40 ABCD > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_wrong_notation.txt
if ERRORLEVEL 1 goto err
timeout /t 5
%PROGRAM% 10 2 ABCD > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_too_small_source_notation.txt
if ERRORLEVEL 1 goto err
timeout /t 5
%PROGRAM% G 10 FFFFFFFF > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_wrong_notation.txt
if ERRORLEVEL 1 goto err
timeout /t 5
%PROGRAM% "" "" > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_param_count.txt
if ERRORLEVEL 1 goto err
timeout /t 5
%PROGRAM% 10 "" 89 > "%DIR%\\temp.txt"
fc.exe "%DIR%\\temp.txt" output_err_param_length.txt
if ERRORLEVEL 1 goto err
timeout /t 5

echo OK
exit 0

:err
echo Program testing failed
timeout /t 5
exit 1
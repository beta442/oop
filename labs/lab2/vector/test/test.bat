set PROGRAM="%~1"
set TEMP_TXT="temp_output.txt"

echo "" > %TEMP_TXT%

rem tests
%PROGRAM% < input1.txt > %TEMP_TXT%
fc.exe %TEMP_TXT% output1.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%
echo "" > %TEMP_TXT%

rem err tests
%PROGRAM% < input_err.txt > %TEMP_TXT%
fc.exe %TEMP_TXT% output_err.txt
if ERRORLEVEL 1 goto err
timeout /t 5
del %TEMP_TXT%

echo OK
exit 0

:err
echo Program testing failed
exit 1
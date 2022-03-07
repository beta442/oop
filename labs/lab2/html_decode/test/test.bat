set PROGRAM="%~1"
set TEMP_TXT="temp_output.txt"

del TEMP_TXT

rem tests
%PROGRAM% < input_default.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_default.txt || goto err
timeout /t 5
del %TEMP_TXT%

%PROGRAM% < input_heavy_default.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_heavy_default.txt || goto err
timeout /t 5
del %TEMP_TXT%

%PROGRAM% < input_only_html_codes.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_only_html_codes.txt || goto err
timeout /t 5
del %TEMP_TXT%

rem err tests
%PROGRAM% < input_empty.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_empty.txt || goto err
timeout /t 5
del %TEMP_TXT%

echo OK
exit 0

:err
del %TEMP_TXT%
echo Program testing failed
exit 1
set PROGRAM="%~1"
set TEMP_TXT="temp_output.txt"

del TEMP_TXT

rem tests
%PROGRAM% dict1.txt < input1.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output1.txt || goto err
timeout /t 5
del %TEMP_TXT%

rem err tests
%PROGRAM% admin_protected_dict.txt < input1.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_err_dict.txt || goto err
timeout /t 5
del %TEMP_TXT%

%PROGRAM% input_err_empty.txt < input1.txt > %TEMP_TXT% || goto err
fc.exe %TEMP_TXT% output_err_dict.txt || goto err
timeout /t 5
del %TEMP_TXT%

echo OK
exit 0

:err
echo Program testing failed
exit 1
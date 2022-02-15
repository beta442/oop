set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

rem %PROGRAM% > nul
rem if NOT ERRORLEVEL 1 goto err

%PROGRAM% input2.txt "%DIR%\output2.txt" 1231234 cat
if ERRORLEVEL 1 goto err
fc.exe input2.txt "%DIR%\output2.txt"

%PROGRAM% input3.txt "%DIR%\output3.txt" o ooooo
if ERRORLEVEL 1 goto err
fc.exe input3.txt "%DIR%\output3.txt"

%PROGRAM% input4.txt "%DIR%\output4.txt" "" ""
if ERRORLEVEL 1 goto err
fc.exe input4.txt "%DIR%\output4.txt"

%PROGRAM% input_none.txt "%DIR%\output2.txt" 1231234 cat
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
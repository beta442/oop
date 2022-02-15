set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

rem %PROGRAM% > nul
rem if NOT ERRORLEVEL 1 goto err

%PROGRAM% input1.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input2.txt
if ERRORLEVEL 1 goto err

%PROGRAM% input3.txt
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
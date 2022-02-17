set PROGRAM="%~1"
set DIR="%TEMP%"
rem set DIR="%CD%"

rem %PROGRAM% > nul
rem if NOT ERRORLEVEL 1 goto err

%PROGRAM% 16 22 -FFFFFFF
if ERRORLEVEL 1 goto err

%PROGRAM% 16 22 1FFFFFFF
if ERRORLEVEL 1 goto err

%PROGRAM% 0 40 ABCD

%PROGRAM% 10 2 ABCD

%PROGRAM% 36 2 ZZZZ

%PROGRAM% "" "" ""

%PROGRAM% 16 10 FFFFFFFF

%PROGRAM% G 10 FFFFFFFF
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
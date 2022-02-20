set PROGRAM="%~1"

rem tests
%PROGRAM% input1.txt output1.txt

err params
%PROGRAM% asdsa sadsad
%PROGRAM% input_empty.txt output1.txt
%PROGRAM% input1.txt not_exist.txt
%PROGRAM% "" "" ""
if ERRORLEVEL 1 goto err

echo OK
exit 0

:err
echo Program testing failed
exit 1
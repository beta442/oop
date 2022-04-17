f = open('test_recursive.txt', 'w')
data = "let x=1\nfn x2=x+x\n"
for i in range(3, 999999):
    data += "fn x" + str(i) + "=x" + str(i - 1) + "+x\n"
    f.write(data)
    data = ""
f.write("print x999998\n")
f.write("let x=2\n")
f.write("print x999998\n")
f.close()

f = open('test_fibb.txt', 'w')
data = ""
f.write("let v0=0\n");
f.write("let v1=1\n");
f.write("fn fib0=v0\n");
f.write("fn fib1=v1\n");
for i in range(2, 50):
    data += "fn fib" + str(i) + "=fib" + str(i - 1) + "+fib" + str(i - 2) + "\n"
    f.write(data);
    data = ""
f.write("printfn\n");
f.write("let v0=1\n");
f.write("let v1=1\n");
f.write("printfn\n");
f.close();

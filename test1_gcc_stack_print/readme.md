## Userspace demo
`test1/main.c` is a demo of user's application, use 
```
$test1: gcc -o main main.c
```
to complie. Then, use following command to run this demo:
```
$test1: ./main
$out> 	a b c d e f g h i
  	a b c d e f g h i
  	a b c d e f g h i
```


## Our workspace
`test2/` is our main workspace to capture user-application systemcall on `malloc(2)` and `free(1)`
The Makefile is already done, use 
```
$test2: make
```
to update the Mem.so for every modification

+ note: since ``printf(...)`` also use `malloc(2)` to alloc a buffer, in mem.c, use `fprintf(stderr,xxx)` intead of `printf`. Otherwise, core dump occures.



## Load Mem.so into userspace
in the terminal used to run `test1/main`, before run, type:
```
export LD_PRELOAD=/home/xx/test2xxx/Mem.so     # notice: use absolute path of Mem.so
```
this will load Mem.so into *this terminal* . From now on, all following processes in *this terminal* will firstly call our func with the same name (now, we only capture to systemcall `malloc` and ``).
Then:
```
./main
```
you will find there are something diff. from before, the user application will firstly enter our `mem.c:malloc(2)`, print sth. , then call the real `malloc(2)` in our logic., the out put is:
```
[malloc] request:10
[malloc] request:1024
a b c d e f g h i 
[free] free
[malloc] request:10
a b c d e f g h i 
[free] free
[malloc] request:10
a b c d e f g h i 
[free] free

```


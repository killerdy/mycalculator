## Introduction
这是一款采用编译技术，将用户输入命令通过词法分析语法分析翻译为栈式字节码并执行的软件。支持用户自定义变量和函数。

## How to build
1. install cmake 
2. `mkdir build && cd build && cmake .. -G'Unix Makefiles'`cd build
3. `make -j4` 取决于CPU核心数量
## Authors

killerdy 2024

## Instance
```
f(a,b)=b*a+1
g(a,b,c)=a+f(b,c)
a=10
b=c=20
g(a,b,c)
RESULT:411
d=3.1
sin(d)  
RESULT:0.041581



```
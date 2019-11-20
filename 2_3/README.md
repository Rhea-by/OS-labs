## 内核模块

### 实验目的

模块是Linux系统的一种特有机制，可用以动态扩展操作系统内核功能。编写实现某些特定功能的模块，将其作为内核的一部分在管态下运行。本实验通过内核模块编程在/porc文件系统中实现系统时钟的读操作接口。

### 实验内容

设计并构建一个在/proc文件系统中的内核模块clock，支持read()操作，read()返回值为一字符串，其中包块一个空各分开的两个子串，为别代表xtime.tv_sec和xtime.tv_usec。

### 实验原理

Linux模块是一些可以作为独立程序来编译的函数和数据类型的集合。在装载这些模块式，将它的代码链接到内核中。Linux模块可以在内核启动时装载，也可以在内核运行的过程中装载。如果在模块装载之前就调用了动态模块的一个函数，那么这次调用将会失败。如果这个模块已被加载，那么内核就可以使用系统调用，并将其传递到模块中的相应函数。

### 使用命令

1. 使用Makefile编译clock.c生成 clock.o
`make`

2. 加载clock.o到Linux内核
在系统root用户下运行：
`insmod clock.ko`

3. 使用gettime.c测试

4. 卸载内核模块
`rmmod clock.o`

### 参考链接

http://edward-zhu.github.io/special/os_exp/2015/01/02/exp-2.3.html

https://stackoverflow.com/questions/14818084/what-is-the-proper-include-for-the-function-sleep-in-c

https://gitlab.freedesktop.org/lyudess/linux/commit/b42d1d6b5b789c41dacbe2bc192c7b359d109d7b

https://stackoverflow.com/questions/8516021/proc-create-example-for-kernel-module

https://github.com/linuxdeepin/deepin-anything/issues/10


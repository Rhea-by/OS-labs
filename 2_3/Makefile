# obj-m := clock.o   #你要编译的模块名称   这里必须和$(PWD)目录下C程序文件的名称相对应，如果C程序文件为helloword.c，那么必须修改 成obj-m=helloword.o

# # KERN_DIR = /home/gqb/development/linux-kernel-2.6.37        #内核源码路径
# # KERN_DIR = /usr/src/$(shell uname -r)
# KERN_DIR = /lib/modules/$(shell uname -r)/build


# all:
# 	make -C $(KERN_DIR) M=$(shell pwd) modules  CROSS_COMPILE=arm-linux-    ARCH=arm   #进入内核源码路径，执行#make modules

# clean:                                 
# 	make -C $(KERN_DIR) M=$(shell pwd) modules clean
# 	rm -rf modules.order



obj-m += clock.o # 添加目标文件
KERNEL_DIR = /lib/modules/$(shell uname -r)/build # 设置内核文件位置
MODULEDIR := $(shell pwd) # 设置生成的模块文件位置
modules:
	make -C $(KERNEL_DIR) M=$(MODULEDIR) modules # 使用KMAKE来生成模块
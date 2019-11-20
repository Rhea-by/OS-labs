## 内核定时器

1. 用定时器ITIMER_REAL实现gettimeofday的功能。使其一秒钟产生一个信号，
计算已经过的秒数

设计思路：
设置定时器ITIMER_REAL间隔为一秒钟。并为计时到时设定信号处理程序，即singal(SIGALRM,…)，使其输出当前所记时间

2. 记录一个进程运行时所占用的real time, cpu time,user time ,kernel time。

设计思路：
任务开始前设置好定时器ITIMER_REAL，ITIMER_VIRTUAL，ITIMER_PROF,即其相应的信号处理程序。在任务执行过程中内核定时器通过产生等间隔的信号来记录进程所需的各种时间参量，并在任务结束后打印出来。

3. 编写一个主程序产生两个子进程，分别低轨计算N =20，30，36的Fibonacci序列。分别对三个进程计算相应的real time, cpu time,user time ,kernel time。

设计思路：
与（2）原理基本相同，不同的只是在任务开始前要分别设定好每个进程的定时器，而且其最终的实验结果也由相应进程自身打印出来。

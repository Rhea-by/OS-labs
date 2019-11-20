#define _GNU_SOURCE

#define MODULE_NAME "clock"

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/time.h>

int clock_proc_show(struct seq_file * m, void * v) {
	// struct timeval xtime;
	// do_gettimeofday(&xtime); // 获取系统时间
    // do_gettimeofday is out of date since kernel 3.18
    // https://github.com/lwfinger/rtlwifi_new/issues/449

    struct timespec64 xtime;
    // xtime = current_kernel_time64();
    	ktime_get_coarse_real_ts64(&xtime);
    //https://gitlab.freedesktop.org/lyudess/linux/commit/b42d1d6b5b789c41dacbe2bc192c7b359d109d7b
	// 将系统时间写入proc文件中
	seq_printf(m, "%llu, %lu\n", xtime.tv_sec, xtime.tv_nsec); 
	printk("clock: read_func()\n");
	return 0;
}

int clock_proc_open(struct inode * inode, struct file * file) {
	// 使用single_open操作来打开顺序文件
	return single_open(file, clock_proc_show, NULL);
}

struct proc_dir_entry * proc_my_clock;

// 文件操作结构体
const struct file_operations clock_proc_fops = {
	.owner = THIS_MODULE,
	.open = clock_proc_open, // 使用clock_proc_open()方法来打开文件
	.read = seq_read, // 使用seq_read()方法以顺序文件方式读取文件
	.llseek = seq_lseek,
	.release = single_release,
};

int __init init_clock(void)
{
	printk("clock: init_module()\n");
	// 创建一个proc模块
	proc_my_clock=proc_create("clock", 0, NULL, &clock_proc_fops);
	printk(KERN_INFO"%s %s has initialized.\n",
			MODULE_NAME, "1.0");
	return 0;
}

void __exit cleanup_clock(void)
{
	printk("clock: cleanup_module()\n");
	remove_proc_entry("clock", NULL);
	printk(KERN_INFO"%s %s has removed.\n",
			MODULE_NAME, "1.0");
}

// 设置初始化模块方法为init_clock()
module_init(init_clock);
// 设置卸载模块方法为cleanup_clock()
module_exit(cleanup_clock);
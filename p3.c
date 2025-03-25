#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>
#include <asm/param.h>

#define HELLO_PROC "hello"
#define JIFFIES_PROC "jiffies"
#define SECONDS_PROC "seconds"

static unsigned long start_jiffies;

// ---------- /proc/hello ----------
static int hello_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello World A1115530\n");
    return 0;
}

// ---------- /proc/jiffies ----------
static int jiffies_show(struct seq_file *m, void *v)
{
    seq_printf(m, "%lu\n", jiffies);
    return 0;
}

// ---------- /proc/seconds ----------
static int seconds_show(struct seq_file *m, void *v)
{
    unsigned long seconds = (jiffies - start_jiffies) / HZ;
    seq_printf(m, "%lu\n", seconds);
    return 0;
}

// ---------- 開啟與操作共用 ----------
static int proc_open_hello(struct inode *inode, struct file *file) {
    return single_open(file, hello_show, NULL);
}
static int proc_open_jiffies(struct inode *inode, struct file *file) {
    return single_open(file, jiffies_show, NULL);
}
static int proc_open_seconds(struct inode *inode, struct file *file) {
    return single_open(file, seconds_show, NULL);
}

// ---------- 共用 FOPS ----------
static const struct file_operations hello_ops = {
    .owner = THIS_MODULE,
    .open = proc_open_hello,
    .read = seq_read,
    .release = single_release,
};

static const struct file_operations jiffies_ops = {
    .owner = THIS_MODULE,
    .open = proc_open_jiffies,
    .read = seq_read,
    .release = single_release,
};

static const struct file_operations seconds_ops = {
    .owner = THIS_MODULE,
    .open = proc_open_seconds,
    .read = seq_read,
    .release = single_release,
};

// ---------- 模組載入 ----------
static int __init simple_proc_init(void)
{
    start_jiffies = jiffies;

    proc_create(HELLO_PROC, 0, NULL, &hello_ops);
    proc_create(JIFFIES_PROC, 0, NULL, &jiffies_ops);
    proc_create(SECONDS_PROC, 0, NULL, &seconds_ops);

    printk(KERN_INFO "Proc modules loaded. A1115530\n");
    return 0;
}

// ---------- 模組卸載 ----------
static void __exit simple_proc_exit(void)
{
    remove_proc_entry(HELLO_PROC, NULL);
    remove_proc_entry(JIFFIES_PROC, NULL);
    remove_proc_entry(SECONDS_PROC, NULL);

    printk(KERN_INFO "Proc modules removed. A1115530\n");
}

module_init(simple_proc_init);
module_exit(simple_proc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A1115530");
MODULE_DESCRIPTION("Combined /proc module for hello, jiffies, seconds");

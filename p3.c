#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <asm/param.h>
#include <linux/hash.h>
#include <linux/gcd.h>

int __init simple_init(void){
	printk(KERN_INFO "loading kernel moduke A1115530\n");
	printk(KERN_INFO "HZ = %d\n",HZ);
	printk(KERN_INFO "jiffies (init) = %li\n",jiffies);
	printk(KERN_INFO "GOLDEN_RATIO_PRIME = %lu\n",GOLDEN_RATIO_PRIME);
	return 0;
}

void __exit simple_exit(void){
	printk(KERN_INFO "Removing Kernel Moduke A1115530\n");
	printk(KERN_INFO "jiffies (exit) = %lu\n",jiffies);
	printk(KERN_INFO "gcd(3300,24) = %lu\n",gcd(3300,24));
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("simple kernel module for CSC061");
MODULE_AUTHOR("A1115530");

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "mydriver"

static char msg[256] = "Hello from my driver!";

static ssize_t my_read(struct file *file, char __user *buf, size_t len, loff_t *off)
{
    if (*off > 0) return 0;
    if (copy_to_user(buf, msg, strlen(msg))) return -EFAULT;
    *off = strlen(msg);
    return *off;
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t len, loff_t *off)
{
    if (len > 255) len = 255;
    if (copy_from_user(msg, buf, len)) return -EFAULT;
    msg[len] = '\0';
    printk(KERN_INFO "mydriver: received: %s\n", msg);
    return len;
}

static const struct proc_ops my_fops = {
    .proc_read = my_read,
    .proc_write = my_write,
};

static int __init my_init(void)
{
    proc_create(PROC_NAME, 0666, NULL, &my_fops);
    printk(KERN_INFO "mydriver: loaded!\n");
    return 0;
}

static void __exit my_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "mydriver: unloaded!\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("My custom driver for OnePlus Ace 5");
MODULE_AUTHOR("Your Name");
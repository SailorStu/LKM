#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>


static void read_file(char *filename)
{
    #define BUF_SIZE 256
    struct file *fp;
    char buf[BUF_SIZE+1];
    __kernel_loff_t pos = 0;
    size_t count = BUF_SIZE;
    size_t ret;

    fp = filp_open(filename, O_RDONLY, 0);
    if (IS_ERR(fp)) {
        printk(KERN_ERR "Error opening file %s\n", filename);
        return;
    }
    do {
        ret = kernel_read(fp, buf, count, &pos);
        if (ret < 0) {
            printk(KERN_ERR "Error reading file %s\n", filename);
            break;
        }
        buf[ret] = '\0';
        printk(KERN_INFO "%s", buf);
    } while (ret == count);
    printk(KERN_INFO "\n=============================\n");
    filp_close(fp, NULL);
}

static int __init test_init(void)
{
    printk(KERN_INFO "Reading /etc/shadow\n");
    read_file("/etc/shadow");
    return 0;
}

static void __exit test_exit(void){ 
    printk(KERN_INFO "\nModule Exiting\n");
}

MODULE_LICENSE("GPL");
module_init(test_init);
module_exit(test_exit);

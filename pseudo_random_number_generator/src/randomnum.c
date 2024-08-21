#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include "randomnum.h"

static int major_number;
static struct class *randomnum_class = NULL;
static struct device *randomnum_device = NULL;

static int randomnum_open(struct inode *inode, struct file *file){
    pr_info("randomnum: Device has beed opened\n");
    return 0;
}

static ssize_t randomnum_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    int random_number;
    ssize_t bytes_read;

    // Generate a random number
    get_random_bytes(&random_number, sizeof(random_number));

    // Copy the random number to the user space
    bytes_read = sizeof(random_number);
    if(copy_to_user(buffer, &random_number, bytes_read) != 0){
        pr_info("randomnum: Failed to return random number to the user\n");
        return -EFAULT;
    }
    pr_info("randomnum: Random number generated and sent to the user\n");
    return bytes_read;
}

static int randomnum_release(struct inode *inode, struct file *file){
    pr_info("randomnum: Device successfully closed\n");
    return 0;
}

static struct file_operations fops = {
    .open = randomnum_open,
    .read = randomnum_read,
    .release = randomnum_release,
};

static int __init randomnum_init(void){
    // Register a major number dynamically
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if(major_number < 0){
        pr_err("randomnum: Failed to register a major number\n");
        return major_number;
    }
    pr_info("randomnum: Registered correctly with major number %d\n", major_number);

    // Register the device class
    randomnum_class = class_create(THIS_MODULE, CLASS_NAME);
    if(IS_ERR(randomnum_class)){
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("randomnum: Failed to register device class\n");
        return PTR_ERR(randomnum_class);
    }

    pr_info("randomnum: Device class registered correctly\n");

    // Register the device driver
    randomnum_device = device_create(randomnum_class, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if(IS_ERR(randomnum_device)){
        class_destroy(randomnum_class);
        unregister_chrdev(major_number, DEVICE_NAME);
        pr_err("randomnum: Failed to create the device\n");
        return PTR_ERR(randomnum_device);
    }
    pr_info("randomnum: Device class created correctly\n");

    return 0;

}

static void __exit randomnum_exit(void){
    device_destroy(randomnum_class, MKDEV(major_number, 0));
    class_unregister(randomnum_class);
    class_destroy(randomnum_class);
    unregister_chrdev(major_number, DEVICE_NAME);
    pr_info("randomnum: Module unloaded\n");
}

module_init(randomnum_init);
module_exit(randomnum_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sumit Patel");
MODULE_DESCRIPTION("Pseudo Random Number Generator");
MODULE_VERSION("1.0");

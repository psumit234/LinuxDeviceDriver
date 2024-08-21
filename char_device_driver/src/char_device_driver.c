#include "char_device_driver.h"
#define DEVICE_NAME "char_device_driver"
#define BUF_LEN 80
#define MAJOR_NUM 108

static int major;
static char message[BUF_LEN] = {0};
static struct cdev c_dev;
static dev_t dev_num;

// File Operations prototypes
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

// File operations structure
static struct file_operations fops = {
    .open = device_open,
    .read = device_read,
    .release = device_release,
    .write = device_write
};

// Init Module
static int __init char_device_init(void) {
    int result;

    // Register device number
    dev_num = MKDEV(MAJOR_NUM, 0);
    result = register_chrdev_region(dev_num, 1, DEVICE_NAME);
    if (result < 0) {
        printk(KERN_WARNING "Can't get major number %d\n", MAJOR_NUM);
        return result;
    }

    // Initialize cdev structure
    cdev_init(&c_dev, &fops);
    c_dev.owner = THIS_MODULE;

    result = cdev_add(&c_dev, dev_num, 1);
    if (result < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_WARNING "Error %d adding char_device_driver\n", result);
        return result;
    }
    printk(KERN_INFO "Char Device Driver registered Successfully\n");
    return 0;
}

// Exit Module
static void __exit char_device_exit(void) {
    cdev_del(&c_dev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Char Device Driver unregistered Successfully\n");
}

// Open Device
static int device_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Release Device
static int device_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// Read from Device
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
    int bytes_read = 0;
    if (*message == 0) {
        return 0;
    }
    while (length && *message) {
        put_user(*(message++), buffer++);
        length--;
        bytes_read++;
    }
    return bytes_read;
}

// Write to Device
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
    if (len > BUF_LEN - 1) {
        printk(KERN_WARNING "Input exceeds buffer length\n");
        return -EINVAL;
    }
    snprintf(message, BUF_LEN, "%s", buff);
    return len;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sumit Kumar Patel");
MODULE_DESCRIPTION("A simple character device driver");
MODULE_VERSION("1.0");

module_init(char_device_init);
module_exit(char_device_exit);
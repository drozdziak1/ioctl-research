#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

long my_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg);

struct file_operations ioctl_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = my_unlocked_ioctl,
};

dev_t ioctl_dev;

struct cdev ioctl_cdev;

int ioctl_init(void)
{
	int ret = 0;

	ret = alloc_chrdev_region(&ioctl_dev, 0, 1, "ioctl_module");
	if(ret) {
		printk(KERN_ERR "%s: chrdev allocation failed\n", __FUNCTION__);
		goto fail_alloc_chrdev;
	}

	cdev_init(&ioctl_cdev, &ioctl_fops);

	ret = cdev_add(&ioctl_cdev, ioctl_dev, 1);
	if(ret) {
		printk(KERN_ERR "%s: cdev_add() failed\n", __FUNCTION__);
		goto fail_cdev_add;
	}

	return 0;

fail_cdev_add:
	unregister_chrdev_region(ioctl_dev, 1);
fail_alloc_chrdev:
	return ret;
}

void ioctl_exit(void)
{
	cdev_del(&ioctl_cdev);
	unregister_chrdev_region(ioctl_dev, 1);
}

long my_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	printk(KERN_DEBUG "%s: Got an ioctl!\n", __FUNCTION__);

	return 0;
}

module_init(ioctl_init);
module_exit(ioctl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Stan Drozd <drozdziak1@gmail.com>");
MODULE_DESCRIPTION("A simple unlocked_ioctl() file operation implementation");

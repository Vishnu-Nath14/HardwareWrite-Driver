#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/string.h>
#include <linux/device.h>
#include <linux/blkdev.h>
#include <linux/slab.h>
#define SECTOR_SIZE 512


MODULE_LICENSE("GPL");

static char *kernel_buffer;

dev_t deviceNumber;
static struct cdev mydev;
static struct class *my_class;
static struct block_device *bdev;
static struct file *bdev_file;


static ssize_t read(
    struct file *file,
    char __user *userbuffer,
    size_t count,
    loff_t *offset
)
{
        size_t len=strlen(kernel_buffer);

        if(*offset>=len){
            return 0;
        }

        if(count>len-*offset){
            count=len-*offset;
        }

        if(copy_to_user(userbuffer,kernel_buffer,count)){
            return -EFAULT;
        }
        *offset=*offset+count;
        return count;
}

static ssize_t write(
    struct file *file,
    const char __user *userbuffer,
    size_t count,
    loff_t *offset
){
    struct page *page;
    struct bio *bio;
    unsigned int page_offset;
    int add;
    int ret;
  
    if(count>SECTOR_SIZE){
        count=SECTOR_SIZE;
    }

    if(copy_from_user(kernel_buffer,userbuffer,count)){
        return -EFAULT;
    };

    page=virt_to_page(kernel_buffer);
    page_offset=offset_in_page(kernel_buffer);

    pr_info("MYDRIVER: buffer=%px page=%px offset=%u count=%zu\n",
        kernel_buffer, page, page_offset, count);

    pr_info("MYDRIVER: allocating BIO, bdev=%px\n", bdev);

    bio=bio_alloc(
        bdev,
        1,
        REQ_OP_WRITE,
        GFP_KERNEL
    );

    if(!bio){
        pr_info("Error");
        return -ENOMEM;
    }

    pr_info("MYDRIVER: BIO allocated successfully: %px\n", bio);
    
    add=bio_add_page(
        bio,
        page,
        SECTOR_SIZE,
        page_offset
    );

    if (add != count) {
        pr_err("bio_add_page did not accept all data\n");
        bio_put(bio);
        return -EIO;
}

    bio->bi_iter.bi_sector=0;

    pr_info("MYDRIVER: bio bdev=%px sector=%llu size=%u\n",
        bio->bi_bdev,
        (unsigned long long)bio->bi_iter.bi_sector,
        bio->bi_iter.bi_size);

    pr_info("MYDRIVER: submitting BIO sector=%llu len=%zu\n",
        (unsigned long long)bio->bi_iter.bi_sector,
        count);

    ret=submit_bio_wait(bio);

    pr_info("MYDRIVER: data = %*ph\n", 16, kernel_buffer);

    pr_info("MYDRIVER: submit_bio_wait returned %d\n", ret);

    if (ret < 0) {
       bio_put(bio);
       return ret;
   }
    bio_put(bio);
    return count;

}

static struct file_operations ops={
    .owner=THIS_MODULE,
    .read=read,
    .write=write
};

static int __init entry(void){

    kernel_buffer=kmalloc(512,GFP_KERNEL);

    if(!kernel_buffer){
        return -ENOMEM;
    }
    int ret=alloc_chrdev_region(&deviceNumber,0,1,"myDevice");

    if(ret<0){
        pr_info("Failed to allocate a device number");
        return ret;
    }
    cdev_init(&mydev,&ops);
    ret=cdev_add(&mydev,deviceNumber,1);

    if(ret<0){
        unregister_chrdev_region(deviceNumber,1);
        pr_info("Failed to add the device");
        return ret;
    }

    my_class=class_create("myDevice");

    if(IS_ERR(my_class)){
        cdev_del(&mydev);
        unregister_chrdev_region(deviceNumber,1);
        return PTR_ERR(my_class);
    }

    if (IS_ERR(device_create(
        my_class,
        NULL,
        deviceNumber,
        NULL,
        "mydevice")))
    {
        pr_err("Failed to create device\n");

        class_destroy(my_class);
        cdev_del(&mydev);
        unregister_chrdev_region(deviceNumber, 1);

        return -EINVAL;
    }

    bdev_file=bdev_file_open_by_path(
        "/dev/vdb",
        BLK_OPEN_WRITE,
        NULL,
        NULL
    );
    if(IS_ERR(bdev_file)){
        pr_info("The path cannot be accessed");
        return PTR_ERR(bdev_file);
    }

    bdev=file_bdev(bdev_file);

    return 0;

}

static void __exit out(void){
    kfree(kernel_buffer);
    device_destroy(my_class,deviceNumber);
    class_destroy(my_class);
    cdev_del(&mydev);
    unregister_chrdev_region(deviceNumber,1);
}

module_init(entry);
module_exit(out);
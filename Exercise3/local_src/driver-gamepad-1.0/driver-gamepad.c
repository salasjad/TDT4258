#include <linux/module.h>
#include <linux/version.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <asm/signal.h>
#include <asm/siginfo.h>
#include "efm32gg.h"

#define DRIVER_NAME         "driver-gamepad"
#define GPIO_EVEN_IRQ       17
#define GPIO_ODD_IRQ        18
 
static dev_t first; // Global variable for the first device number
static struct cdev c_dev; // Global variable for the character device structure
static struct class *cl; // Global variable for the device class
static struct resource *gpio_pa;
static struct resource *gpio_pc;
static struct fasync_struct* async_queue;

u16 last_button_pressed = 0;

static int my_open(struct inode *i, struct file *f);
static int my_close(struct inode *i, struct file *f);
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off);
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off);
static irqreturn_t GPIO_irq_handler(int irq, void *dev_id, struct pt_regs *regs);
static int my_fasync(int fd, struct file* filp, int mode);
static int __init gamepad_init(void);
static void __exit gamepad_exit(void);
int allocate_memory(void);
int register_driver(void);
int interrupts_init(void);
void GPIO_init(void);

static struct file_operations pugs_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write,
    .fasync = my_fasync 
};


static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}

static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}

// returns LAST PRESSED BUTTON!
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    int status;
    printk(KERN_INFO "Driver: read()\n"); 

  
    printk(KERN_INFO "Buttons state: 0x%X\n", last_button_pressed);
    status = copy_to_user(buf, &last_button_pressed, len);
    return sizeof(last_button_pressed); // not sure about sizeof in a driver
}

// we don't really care about writing 
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: write()\n");
    return len;
}

static int my_fasync(int fd, struct file* filp, int mode)
{
    return fasync_helper(fd, filp, mode, &async_queue);
}

// interrupt handler
static irqreturn_t GPIO_irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
    void *gpio_pa_addr;
  
    printk(KERN_ALERT "Handling GPIO interrupt\n");
    gpio_pa_addr = ioremap(gpio_pa->start, GPIO_PA_LENGTH);
  
    last_button_pressed = readw(gpio_pa_addr + IF_OFFSET); // read interrupt source
    writel(last_button_pressed, gpio_pa_addr + IFC_OFFSET); // clear interrupt
    
    if (async_queue) 
    {
        kill_fasync(&async_queue, SIGIO, POLL_IN);
    }
    return IRQ_HANDLED;
}

int allocate_memory()
{
    // allocate I/O memory
    if ((gpio_pa = request_mem_region(GPIO_PA_BASE, GPIO_PA_LENGTH, DRIVER_NAME "-GPIO_PA")) == NULL)
    {
        printk(KERN_ALERT "Error requesting GPIO_PA memory\n");
        return -1;
    }
    // ioremap_nocache(gpio_pa->start, GPIO_PA_LENGTH);
  
    if ((gpio_pc = request_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH, DRIVER_NAME "-GPIO_PC")) == NULL)
    {
        printk(KERN_ALERT "Error requesting GPIO_PC memory\n");
        return -1;
    }
    return 0;
}

int register_driver()
{
    if (alloc_chrdev_region(&first, 0, 1, DRIVER_NAME ) < 0)
    {
        return -1;
    }
    if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
    {
        unregister_chrdev_region(first, 1);
        return -1;
    }
    if (device_create(cl, NULL, first, NULL, DRIVER_NAME) == NULL)
    {
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }

    cdev_init(&c_dev, &pugs_fops);
    if (cdev_add(&c_dev, first, 1) == -1)
    {
        device_destroy(cl, first);
        class_destroy(cl);
        unregister_chrdev_region(first, 1);
        return -1;
    }
    return 0;
}

int interrupts_init()
{
  if (request_irq(GPIO_EVEN_IRQ, (irq_handler_t)GPIO_irq_handler, 0, DRIVER_NAME, &c_dev) || // EVEN
      request_irq(GPIO_ODD_IRQ, (irq_handler_t)GPIO_irq_handler, 0, DRIVER_NAME, &c_dev)) // ODD
  {
      return -1;
  }
  return 0;  
}

void GPIO_init()
{
    void *gpio_pa_addr;
    void *gpio_pc_addr;
  
    // set up GPIO registers!
    gpio_pa_addr = ioremap(gpio_pa->start, GPIO_PA_LENGTH);
    gpio_pc_addr = ioremap(gpio_pc->start, GPIO_PC_LENGTH);
    writel(0x33333333, gpio_pc_addr + MODEL_OFFSET); // set pins as INPUT
    writel(0xFF, gpio_pc_addr + DOUT_OFFSET); // internal pullup
    writel(0x22222222, gpio_pa_addr + EXTIPSELL_OFFSET); // GPIO_PC bits enable interrupt
  
    writel(0xFF, gpio_pa_addr + EXTIFALL_OFFSET); // enable falling edge interrupt
    writel(0xFFFF, gpio_pa_addr + IFC_OFFSET); // !!!!!!!!IMPORTANT!!!!!!!!!! clear interrupt flags
    writel(0xFF, gpio_pa_addr + IEN_OFFSET); // enable  interrupts
}
 
static int __init gamepad_init(void) // Constructor 
{
  int status;
 
  // allocate I/O memory
  if (allocate_memory() != 0)
  {
      return -1;
  }

  printk(KERN_INFO "Gamepad driver registering\n");
  // register driver
  if ((status = register_driver()) != 0)
  {
      return status;
  }

  GPIO_init();

  // set up GPIO interrupts!
  if (interrupts_init() != 0) 
  {
      printk(KERN_ALERT "Error: Unable to request IRQ\n");
      device_destroy(cl, first);
      class_destroy(cl);
      unregister_chrdev_region(first, 1);
      return -1;
  }  
  return 0;
}


static void __exit gamepad_exit(void) // Destructor 
{
    cdev_del(&c_dev);
    device_destroy(cl, first);
    class_destroy(cl);
    unregister_chrdev_region(first, 1);
    // unregister interrupts
    free_irq(GPIO_EVEN_IRQ, &c_dev);
    free_irq(GPIO_ODD_IRQ, &c_dev);
    // release reserved memory
    release_mem_region(GPIO_PA_BASE, GPIO_PA_LENGTH);
    release_mem_region(GPIO_PC_BASE, GPIO_PC_LENGTH);
    printk(KERN_INFO "Gamepad driver unregistered");
}
 
module_init(gamepad_init);
module_exit(gamepad_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("David, Salahuddin, Valentin");
MODULE_DESCRIPTION("Gamepad driver v1.0");

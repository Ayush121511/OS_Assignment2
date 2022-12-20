#include <linux/kernel.h>	/* We're doing kernel work */
#include <linux/module.h>	/* Specifically, a module, */
#include <linux/moduleparam.h>	/* which will have params */
#include <linux/unistd.h>	/* The list of system calls */
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include<linux/sched.h>

extern void *sys_call_table[];

pid_t pid;

module_param(pid, pid_t, 0);

asmlinkage int (*org_call)(char,char **,off_t ,int,int ,void *);

asmlinkage int  newSysCall ( char *buf, char **start, off_t offset, int count, int *eof, void *data ){
    int len=0;
    struct task_struct *task_list;


    for_each_process(task_list) {

        len  += sprintf(buf+len, "\n %s %d \n",task_list->comm,task_list->pid);
    }
    
    return len;
}

void create_new_proc_entry()
{
create_proc_read_entry("ps_list",0,NULL,read_proc,NULL);

}

int functn_init (void) {
    int ret;

    create_new_proc_entry();
    return 0;
}

int init_module(){
    printk(KERN_ALERT "%d\n",__NR_open);
    return 0;
}
// void functn_cleanup(void) {
//     remove_proc_entry("ps_list",NULL);
// }

void cleanup_module()
{
	/* 
	 * Return the system call back to normal 
	 */
    printK(KERN_ALERT, "bye");
}

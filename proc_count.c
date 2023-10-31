#include <linux/module.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>

static struct proc_dir_entry *entry;

// show function = gen.s data for /proc file
static int print_proc_count(struct seq_file *m, void *v){
	// represents proc descriptor w all info kern needs abt proc (node in doubly-linked task list)
	struct task_struct *p; 
	int processcount = 0; 
	// iterates through all active processes
	for_each_process(p) {
		processcount++; 
	}
	seq_printf(m, "%d\n", processcount); // functions like printk(), but needs seq_file pointer as arg
	return 0;
}

// create virt file w ^ print_proc_count as show function
static int __init proc_count_init(void)
{
	entry = proc_create_single("count", 0, NULL, print_proc_count); // name of proc file creating, permission mode, parent, show function
	pr_info("proc_count: init\n"); // printk() w log level = KERN_INFO/6 
	                               // spec. importance of message -> kern decides to show message imm.ly or not
	
	return 0;
}

// remove virt file
static void __exit proc_count_exit(void)
{
	proc_remove(entry); // removes virtual file
	pr_info("proc_count: exit\n");
}

module_init(proc_count_init); // defines function to call at module insertion time (insmod)
module_exit(proc_count_exit);  // "                               " removed (rmmod)
                               // wraps mod clean-up code w cleanup_module

MODULE_AUTHOR("Marlee Kitchen");
MODULE_DESCRIPTION("Counts and outputs number of active kernel processes");
MODULE_LICENSE("GPL");

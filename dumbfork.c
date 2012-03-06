// Zhipeng Tian
// zhiptian
// 3/4/12

#include <linux/linkage.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <asm/syscalls.h>

int sys_dumbfork(struct pt_regs *regs)
{
	return do_fork(CLONE_NOW | SIGCHLD, regs->sp, regs, 0, NULL, NULL);
}
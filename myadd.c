// Zhipeng Tian
// zhiptian
// 3/8/12

#include <linux/syscalls.h>
#include <linux/linkage.h>

asmlinkage long sys_myadd(int x, int y)
{
	return x+y;
}
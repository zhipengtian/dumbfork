/* Zhipeng Tian
   Assignment 3
   Phase 1
   3/8/12
*/

#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>

#define sys_myadd      348

int myadd(int x, int y) {
	return syscall(sys_myadd, x, y);
}

int main()
{
	int x, y, result;
	
	printf("You are about to use myadd system call to add two numbers.\n");
	
	printf("Please enter your first number: ");
	scanf("%d", &x);
	
	printf("Please enter your second number: ");
	scanf("%d", &y);
	
	result = myadd(x, y);
	printf("The result is %d.\n", result);
	
	return 0;
}
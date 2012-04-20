#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define sys_dumbfork   347

int main()
{
	pid_t pid;
	clock_t start, end;
	double dif;
	int i;
  	
	int *test = (int*) malloc(sizeof(int) * 1024 * 1024);

	for(i = 0; i < 1024*1024; i++) {
		test[i] = i;
	}


  	//testing fork
  	start = clock();
  
  	for (i = 0; i <= 1000; i++){
    	pid = fork();
    	if (pid == -1)
      		printf("Error! Can't fork!\n");
    	else if (pid == 0) {
      		exit(0);
    	}
  	}
  	end = clock();
  	dif = (double)(end - start) / CLOCKS_PER_SEC;
  	printf("1000 fork system call took %f seconds.\n", dif);
  
 	//testing dumbfork
 	start = clock();
   
  	for (i = 0; i <= 1000; i++){
    	pid = syscall(sys_dumbfork);
		if (pid == -1)
      		printf("Error! Can't dumbfork!\n");
    	else if (pid == 0) {
    	  exit(0);
    	}
  	}
   
   	end = clock();
   	dif = (double)(end - start) / CLOCKS_PER_SEC;
   	printf("1000 dumbfork system call took %f seconds.\n", dif);
  
  	return 0;
}

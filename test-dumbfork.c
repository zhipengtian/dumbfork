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
  time_t start, end;
  double dif;
  int i;
  
  //testing fork
  time(&start);
  
  for (i = 0; i <= 1000; i++){
    pid = fork();
    if (pid == 0) {
      exit(1);
    }
  }
  
  time(&end);
  dif = difftime(end, start);
  printf("1000 fork system call took %.3lf seconds.\n", dif);
  
  //testing dumbfork
  time(&start);
  
  for (i = 0; i <= 1000; i++){
    pid = syscall(sys_dumbfork);
    if (pid == 0) {
      exit(1);
    }
  }
  
  time(&end);
  dif = difftime(end, start);
  printf("1000 dumbfork system call took %.3lf seconds.\n", dif);

  
  return 0;
}
#include <sys/syscall.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define sys_spmap_info   349

int main(int argc, char *argv[]){
  char buff[4096];
  int size = sizeof(buff);
  printf("size is %d\n", size);
  char *p = argv[1];
  if(argc < 2)
    printf("Too few arguments.\n");
  
  else if(!isdigit(*p) && *p) {
    printf("Invaild process ID.\n");
  }
  else {
    int pid = strtol(p,0,0);
    printf("pid %d\n", pid);
    syscall(sys_spmap_info, pid, buff, size);
  }
  printf("%s\n", buff);
  return 0;
}

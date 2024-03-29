// Zhipeng Tian
// zhiptian
// 4/6/12

#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/mm.h>
//#include <linux/path.h>
//#include <linux/dcache.h>
#include <linux/syscalls.h>
#include <linux/linkage.h>
#include <asm/uaccess.h>

asmlinkage long sys_spmap_info(int pid, char *buff, int size)
{
  struct task_struct *task;
  struct mm_struct *mem;
  struct vm_area_struct *vmem;
  unsigned long vma_addr;
  int vma_size;
  char res[size];
  int count;
  
  for_each_process(task) {
    if(task->pid == pid) {
      mem = task->mm;
      break;
    }	
  }
  printk("process id is: %d\n", pid);
  sprintf(res,"process %d\n", pid);
  
  vmem = mem->mmap;
  count = mem->map_count;
  
  /*char *pathname;
    char *tmp;
    struct file *file;
    struct path path;
    const struct path *p;*/
  
  int i;
  for (i=0; i<count; i++){
    vma_addr = vmem->vm_start;
    vma_size = ((vmem->vm_end-vmem->vm_start)/1024);
    sprintf(res+strlen(res), "%-8lx\t%8dk\t", vma_addr, vma_size);
    
    if (vmem->vm_file) {
      /*file = vmem->vm_file;
	path = file->f_path;
	p = (const struct path *)&path;
	tmp = (char *)__get_free_page(GFP_TEMPORARY);
	pathname = d_path(p, tmp, PAGE_SIZE);*/
      sprintf(res+strlen(res), "\t%s\n", "library");
      //free_page((unsigned long)tmp);
    } else {
      if (mem->start_stack >= vmem->vm_start && mem->start_stack <= vmem->vm_end)
	sprintf(res+strlen(res), "\t%s\n", "[ stack ]");
      else if (mem->start_brk >= vmem->vm_start && mem->brk <= vmem->vm_end)
	sprintf(res+strlen(res),"\t%s\n", "[ heap ]");
      else if (mem->start_code >= vmem->vm_start && mem->start_code <= vmem->vm_end)
	sprintf(res+strlen(res),"\t%s\n", "[ code ]");
      else if (mem->start_data >= vmem->vm_start && mem->start_data <= vmem->vm_end)
	sprintf(res+strlen(res),"\t%s\n", "[ data ]");
      else sprintf(res+strlen(res), "\t%s\n", "[ anon ]");
    }
    if (i<(count-1))
      vmem = vmem->vm_next;
  }
  copy_to_user(buff, res, size);
  return 0;
}

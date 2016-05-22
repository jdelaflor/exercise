#include "doggy_process.h"
#include "doggy_process.h"

void * doggy_thread_start(void *arg)
{
  pid_t pid;
  struct thread_info * information;
  int file_descriptor;
  int return_value;
  information = arg;
  char file_name [MAX_BUF_SIZE];
 
  snprintf(file_name, MAX_BUF_SIZE, "/tmp/doggy_%d.log", information->thread_num );  
  while (TRUE)
  {
    pid = fork();
    

    if (pid == ZERO)
    {
      
      /*printf("doggy launched with %d\n", information->thread_num);*/
      file_descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
      dup2(file_descriptor,1);
      close(file_descriptor);
      execl(information->parameters->doggy_path,NULL);
    }
    else if (pid > ZERO)
    {
      information->pid = pid;
      printf("doggy process started with '%d' pid in thread '%d'\n", information->pid, information->thread_num);
      waitpid(pid, &return_value, 0);
      information->restart_times++;
    }
    else
    {
      /*fork failed*/
      printf("fork() failed!\n");
    }
  }
}

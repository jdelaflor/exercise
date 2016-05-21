#include "doggy_process.h"
#include "doggy_process.h"

void * doggy_thread_start(void *arg)
{
  pid_t pid;
  int return_value;
  struct thread_info * information;
  information = arg;

  while (TRUE)
  {
    pid = fork();

    if (pid == ZERO)
    {
      printf("DOGGY %d launched", pid);
      execl(information->parameters->doggy_path,NULL);
    }
    else if (pid > ZERO)
    {
      information->pid = pid;
      printf("WATCHER process started for %d", information->pid);
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

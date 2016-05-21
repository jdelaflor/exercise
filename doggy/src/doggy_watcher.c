#include "doggy_watcher.h"
#include <signal.h>


struct doggy_parameters parameters;
struct thread_info * global_thread_information;

void sighandler(int signum, siginfo_t *info, void *ptr)
{
    printf("Received signal %d\n", signum);
    printf("Signal originates from process %lu\n",
        (unsigned long)info->si_pid);
}

void configure_statistics(void)
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = sighandler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act, NULL);
}


int main(int argc, char *argv[])
{
  int return_value=ERROR;
  int loop_counter=0;
  int rc =0;
  

  
  printf("Doggy Watcher \n");
  

   
  configure_doggy(&parameters);
  /*reserve memory*/
  global_thread_information = malloc((size_t)parameters.number_of_instances * sizeof(struct thread_info));
  /*Configure statistics*/
  configure_statistics();
  /*initialize and launch threads*/  
  for (loop_counter = ZERO; loop_counter < parameters.number_of_instances; loop_counter++)
  {
    global_thread_information[loop_counter].thread_num = ZERO;
    global_thread_information[loop_counter].pid = ZERO;
    global_thread_information[loop_counter].restart_times = ZERO;
    global_thread_information[loop_counter].restart_times = ZERO;
    global_thread_information[loop_counter].parameters=&parameters;
    
    rc = pthread_create(&global_thread_information[loop_counter].thread_id, NULL, doggy_thread_start, (void *)&global_thread_information[loop_counter]);
    if (rc)
    {
       printf("Error creating thread %d\n", loop_counter );
    }
  }
  
  free(global_thread_information);
  while (TRUE)
  {
    printf ("Main thread awake %d\n", global_thread_information[0].thread_num);
     sleep(1);
  }
  return (return_value);
}

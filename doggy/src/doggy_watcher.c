#include "doggy_watcher.h"



int main(int argc, char *argv[])
{
  int return_value=ERROR;
  int loop_counter=0;
  int rc =0;
  
  struct doggy_parameters parameters;
  struct thread_info * global_thread_information;

  
  printf("Doggy Watcher \n");
  

   
  configure_doggy(&parameters);
  /*reserve memory*/
  global_thread_information = malloc((size_t)parameters.number_of_instances * sizeof(struct thread_info));
  /*initialize and launch threads*/  
  for (loop_counter = ZERO; loop_counter < parameters.number_of_instances; loop_counter++)
  {
    global_thread_information[loop_counter].thread_num = loop_counter;
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
    /*Monitorice file size and make the copy*/
    printf ("Main thread awake %d\n", global_thread_information[0].thread_num);
    sleep(1);
  }
  return (return_value);
}

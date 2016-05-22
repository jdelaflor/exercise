#include "doggy_watcher.h"



int main(int argc, char *argv[])
{
  int return_value=ERROR;
  char file_name [MAX_BUF_SIZE];
  char file_name_bkp [MAX_BUF_SIZE];
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
    global_thread_information[loop_counter].log_roll_times = ZERO;
    global_thread_information[loop_counter].restart_times = ZERO;
    global_thread_information[loop_counter].parameters=&parameters;
    
    rc = pthread_create(&global_thread_information[loop_counter].thread_id, NULL, doggy_thread_start, (void *)&global_thread_information[loop_counter]);
    if (rc)
    {
       printf("Error creating thread %d\n", loop_counter );
    }
  }
  
  while (TRUE)
  {
    /*Monitorice file size and make the copy*/
    for (loop_counter = ZERO; loop_counter < parameters.number_of_instances; loop_counter++)
    {
        snprintf(file_name, MAX_BUF_SIZE, "/tmp/doggy_%d.log",global_thread_information[loop_counter].thread_num);
        if (file_size(file_name) >= parameters.log_size)
        {
           /*kill -STOP*/
        snprintf(file_name_bkp, MAX_BUF_SIZE, "/tmp/doggy_%d.log_%d",global_thread_information[loop_counter].thread_num, global_thread_information[loop_counter].log_roll_times);
           if (copy_file(file_name,file_name_bkp) != ERROR) 
           {
             global_thread_information[loop_counter].log_roll_times++;
             if (truncate_file(file_name)==ERROR)
             {
                 printf("Error truncating '%s' \n", file_name);
             }
           } 
           else
           {
             printf("Error copying '%s' to '%s'\n", file_name,file_name_bkp);
           }
   
           /*kill -CONT*/
        }
       
    }
    sleep(FILE_CHECK_SLEEP);
  }
  free(global_thread_information);
  return (return_value);
}

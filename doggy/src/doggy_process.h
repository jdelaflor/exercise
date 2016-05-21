#ifndef __DOGGY_PROCESS_H__
#define __DOGGY_PROCESS_H__
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "doggy_watcher_constants.h"
#include "doggy_watcher_params.h"


struct thread_info {
  pthread_t thread_id;
  pid_t  pid;
  int  thread_num;
  int  restart_times;
  int log_roll_times;
  struct doggy_parameters * parameters;
};

void * doggy_thread_start(void *arg);


#endif

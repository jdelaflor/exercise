#ifndef __DOGGY_WATCHER_PARAMETERS_H__
#define __DOGGY_WATCHER_PARAMETERS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "doggy_watcher_constants.h"

#define MAX_LENGTH 256
#define MAX_LINE_SIZE 1024
#define CONFIG_FILE "doggy_parameters.conf"

/*field names*/
#define INSTANCES "instances"
#define PATH "path"
#define LOGSIZE "size"

/*Default values*/
#define DEFAULT_LOG_SIZE 1024
#define DEFAULT_INSTANCES 2
#define DEFAULT_PATH "./doggy"


struct doggy_parameters
{
  int number_of_instances;
  char doggy_path[MAX_LENGTH];
  /*file size in bytes*/
  long long log_size;
};

int configure_doggy(struct doggy_parameters * parameters);

#endif

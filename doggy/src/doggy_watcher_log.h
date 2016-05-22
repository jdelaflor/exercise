#ifndef __DOGGY_WATCHER_LOG_H__
#define __DOGGY_WATCHER_LOG_H__

#include <sys/stat.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "doggy_watcher_constants.h"

#define MAX_BUFFER_LENGTH 512

off_t file_size(const char *filename);
int copy_file(char * file_source, char * file_des);
int truncate_file(const char *filename);

#endif

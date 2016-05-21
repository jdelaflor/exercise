#ifndef __DOGGY_H__
#define __DOGGY_H__

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

/*Sleep one second*/
#define SLEEP_TIME 1
#define DOGGY_TRUE 1
#define RANDOM_ERROR_CLAUSE 69 
#define NO_ERROR 0
#define ERROR -1
#define BUFFER_SIZE 26
#define DOGGY_MAX_RANDOM 100

int print_time(void);
int wait_for_next_trace(void);
int check_for_random_error(void);
int initialize_random_number_generation(void);

#endif

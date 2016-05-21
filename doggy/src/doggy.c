#include "doggy.h"

int main (int argc, char * argv[])
{
  int return_value = NO_ERROR;

  while (DOGGY_TRUE)
  {
      print_time();
      /*print time printing without CR*/
      printf("Doggy making doggy style traces\n");
      /*wait one second for the next trace*/
      if (ERROR == check_for_random_error())
      {
         /*random error happened
           return ERROR*/
         return_value = ERROR;
         break;
      }
      wait_for_next_trace();
  }

  return (return_value);
}

int print_time(void) 
{
  char buffer[BUFFER_SIZE]; 
  int milliseconds;
  struct tm* tm_info;
  struct timeval tv;
  int return_value=NO_ERROR;

  gettimeofday(&tv, NULL);

  /*round milliseconds*/
  milliseconds = lrint(tv.tv_usec/FTHOUSAND); 
  if (milliseconds>=THOUSAND) 
  { 
    milliseconds -=THOUSAND;
    tv.tv_sec++;
  }

  tm_info = localtime(&tv.tv_sec);

  strftime(buffer, BUFFER_SIZE, "%d:%m:%Y %H:%M:%S", tm_info);
  printf("%s.%03d ", buffer, milliseconds);

  return(return_value);
}

int wait_for_next_trace(void)
{
  int return_value = NO_ERROR;

  sleep(SLEEP_TIME);

  return(return_value);
}

int check_for_random_error (void)
{
   int return_value = NO_ERROR;
   int random_number = rand() % DOGGY_MAX_RANDOM;

   if ( RANDOM_ERROR_CLAUSE == random_number)
   {
     return_value = ERROR;
   }

   return(return_value);
}

int initialize_random_number_generation(void)
{
  int return_value = NO_ERROR;

  srand((unsigned int)time(NULL));

  return(return_value);
}


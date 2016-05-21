#include "doggy_watcher.h"

int main(int argc, char *argv[])
{
  int return_value=ERROR;
  struct doggy_parameters parameters;


  printf("Doggy Watcher \n");

  configure_doggy(&parameters);


  pid_t pid = fork();

  if (pid == ZERO)
  {
    printf("DOGGY");
    return_value = NO_ERROR;
  }
  else if (pid > ZERO)
  {
    printf("WATCHER");
    return_value = NO_ERROR;
  }
  else
  {
    // fork failed
    printf("fork() failed!\n");
    return_value = ERROR;
  }

  return (return_value);
}

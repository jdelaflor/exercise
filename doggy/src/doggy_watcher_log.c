#include "doggy_watcher_log.h"


int copy_file(char * file_source, char * file_des)
{
  char buffer[MAX_BUFFER_LENGTH];
  size_t size;
  int return_value = ERROR;

  int source = open(file_source, O_RDONLY, 0);
  int dest = open(file_des, O_WRONLY | O_CREAT, 0644);

  /*if ((source < ZERO) || (dest < ZERO))
  {*/

    while ((size = read(source, buffer, MAX_BUFFER_LENGTH)) > 0) {
      write(dest, buffer, size);
    }
    close(source);
    close(dest);
    return_value = NO_ERROR; 
  /*}
  else
  {
    return_value = ERROR;
  }*/
  return (return_value);
}

off_t file_size(const char *filename) 
{
  struct stat st; 
  off_t return_value = ERROR;

  if (stat(filename, &st) == 0)
  {
    return_value = st.st_size;
  }

  return (return_value); 
}

int truncate_file(const char *filename)
{
  int return_value = open(filename, O_TRUNC | O_WRONLY);
  if (ERROR != return_value)
  {
    close(return_value);
    return_value = NO_ERROR;
  }
  return (return_value);
}

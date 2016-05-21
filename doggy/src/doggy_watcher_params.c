#include "doggy_watcher_params.h"

void init_parameters (struct doggy_parameters * parameters)
{
  parameters->log_size=DEFAULT_LOG_SIZE;
  parameters-> number_of_instances=DEFAULT_INSTANCES;
  strncpy (parameters->doggy_path,DEFAULT_PATH, MAX_LENGTH);
}

char * trim_string (char * string)
{
  char *string1 = string; 
  char *string2 = &string[strlen (string) - 1];

  while ( (isspace (*string2)) && (string2 >= string1) )
  {
    string2--;
  }
  *(string2+1) = '\0';

  while ( (isspace (*string2)) && (string1 < string2) )
  {
    string1++;
  }

  strcpy (string, string1);

  return (string);
}

void print_configuration(struct doggy_parameters * parameters)
{
  printf("Configured '%s' as '%d' instances.\n", INSTANCES,parameters->number_of_instances);
  printf("Configured '%s' as '%s'.\n", PATH,parameters->doggy_path);
  printf("Configured '%s' as '%lld' bytes.\n", INSTANCES,parameters->log_size);
}

int parse_config (struct doggy_parameters * parameters)
{
  char *string;
  char buffer[MAX_LINE_SIZE];
  int return_value = ERROR;
  char name[MAX_LENGTH];
  char value[MAX_LENGTH];
  long long safety_log_size = DEFAULT_LOG_SIZE;
  int safety_instance_number = DEFAULT_INSTANCES;
  FILE *filepointer = fopen (CONFIG_FILE, "r");
  if (filepointer == NULL)
  {
    return_value = ERROR;
  }
  else 
  {
    /* Get line */
    while ((string = fgets (buffer, sizeof buffer, filepointer)) != NULL)
    {
      /* Remove blank lines and comments */
      if (buffer[0] == '\n' || buffer[0] == '#')
      {
        continue;
      }
      else
      {
        /* Get name/value from current line */
        string = strtok (buffer, "=");
        if (NULL == string)
        {
          continue;
        }
        else
        {
          strncpy (name, string, MAX_LENGTH);
          string = strtok (NULL, "=");
          if (NULL == string)
          {
            continue;
          }
          else
          {
            strncpy (value, string, MAX_LENGTH);
            trim_string (value);
            if (strcmp(name, INSTANCES)==0)
            {
              safety_instance_number = atoi(value);
              if ( 0 > safety_instance_number )
              {
                safety_instance_number = DEFAULT_INSTANCES;
              }
              parameters->number_of_instances=safety_instance_number;
            }
            else if (strcmp(name, PATH)==0)
            {
              strncpy (parameters->doggy_path, value, MAX_LENGTH);
            }
            else if (strcmp(name, LOGSIZE)==0)
            {
              safety_log_size = atoll(value);
              if ( 0 > safety_log_size )
              {
                safety_log_size = DEFAULT_LOG_SIZE;;
              }
              parameters->log_size=safety_log_size;
            }
            else
              printf ("BEWARE: '%s'='%s': Unexpected values.\n", name, value);
           }
         }
       }
    }
    /* Clean and print */
    fclose (filepointer);
    print_configuration(parameters);
    return_value = NO_ERROR;
  }
  return(return_value);
}

int configure_doggy(struct doggy_parameters * parameters)
{
  /*Parameters are initialized if any error happens with configuration file to its default values*/
  init_parameters (parameters);
  return(parse_config (parameters));

}


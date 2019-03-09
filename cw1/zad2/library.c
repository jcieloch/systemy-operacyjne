#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "library.h"

char** new_table(int size)
{
  return (char**)calloc(size, sizeof(char*));
}

searching_parameters actual_search(char* catalog_name, char* file_name)
{
  searching_parameters parameters;
  parameters.catalog_name = catalog_name;
  parameters.file_name = file_name;
  return parameters;
}

int exec_search(char* catalog_name, char* file_name, char* tmp_file_name)
{
  //FILE * tmp = NULL;
  //tmp = fopen(file_name, "w");
  char command[100];
  strcpy(command, "find ");
  strcat(command, catalog_name);
  strcat(command, " -name '");
  strcat(command, file_name);
  strcat(command, "' > ");
  strcat(command, tmp_file_name);

  system(command);

  //fclose(tmp);
  return 0;
}

int write_block(char** table, int table_size, char* tmp_file_name)
{
  int index = 0;
  while(index < table_size && table[index] != NULL)
  {
    index ++;
  }
  FILE * tmp = NULL;
  char* file_name = tmp_file_name;
  tmp = fopen(file_name, "r");
  int file_size = 0;
  struct stat st;
  stat(file_name, &st);
  file_size = st.st_size;
  table[index] = (char*)calloc(file_size, sizeof(char));
  for(int i = 0; i < file_size; i++)
  {
    table[index][i] = fgetc(tmp);
  }
  fclose(tmp);
  return index;
}

int remove_block(char** table, int index)
{
  free(table[index]);
  table[index] = NULL;
  return 0;
}


int remove_table(char** table)
{
  int i = 0;
  while(table[i] != NULL)
  {
    free(table[i]);
    table[i] = NULL;
    i++;
  }
  free(table);
  table = NULL;
  return 0;
}


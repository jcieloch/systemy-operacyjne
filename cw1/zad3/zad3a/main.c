#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/times.h>
#include <dlfcn.h>
#include <stdbool.h>

#ifndef DLL
#include "library.h"
#endif

#ifdef DLL
void * dll;
#endif

clock_t st_time;
clock_t en_time;
struct tms st_cpu;
struct tms en_cpu;


//http://pubs.opengroup.org/onlinepubs/009604599/functions/times.html
void start_clock()
{
    st_time = times(&st_cpu);
}

void end_clock(FILE *destFile)
{
    en_time = times(&en_cpu);
    char buffer[1000] = {0};
    sprintf(buffer, "Real Time: %jd ms, User Time: %jd ms, System Time: %jd ms\n\n",
        (intmax_t)(en_time - st_time),
        (intmax_t)(en_cpu.tms_utime - st_cpu.tms_utime),// / CLOCKS_PER_SEC,
        (intmax_t)(en_cpu.tms_stime - st_cpu.tms_stime));// / CLOCKS_PER_SEC);
    fputs(buffer, destFile);
}

int main(int argc, char *argv[])
{
  //testy:
  //create_table rozmiar search dir file tmp_file_name remove_table
  //create_table rozmiar ((search dir file tmp_file_name)*) remove_table
  //create_table rozmiar ((search dir file tmp_file_name)*) ((remove_block index)*) remove_table
  //create_table rozmiar ((search dir file tmp_file_name remove_block index)*) remove_table


  char** table;
  int table_size;
  if(argc < 2) return 1;
  int i = 1;
  int index[100]; //indexy tablic
  int index_number = 0;

  FILE * tmp = NULL;
  char* file_name = "raport3a.txt";
  tmp = fopen(file_name, "a");

  #ifdef DLL
    dll = dlopen("./my_dynamic_library.so", RTLD_LAZY);

    char** (*new_table)(int) = dlsym(dll, "new_table");
    int (*exec_search)(char*, char*, char*) = dlsym(dll, "exec_search");
    int (*write_block)(char**, int, char*) = dlsym(dll, "write_block");
    int (*remove_block)(char**, int) = dlsym(dll, "remove_block");
    int (*remove_table)(char**) = dlsym(dll, "remove_table");

    start_clock();

    while(i < argc)
    {
      if(!strcmp(argv[i], "create_table"))
      {
        table_size = atoi(argv[i+1]);
        table = new_table(table_size);
        i++;
      }
      else if(!strcmp(argv[i], "search"))
      {
        exec_search(argv[i+1], argv[i+2], argv[i+3]);
        index[index_number] = write_block(table, table_size, argv[i+3]);
        index_number++;
        i+=3;
      }
      else if(!strcmp(argv[i], "remove_block"))
      {
        int index_to_remove = atoi(argv[i+1]);
        remove_block(table, index_to_remove);
        index[index_to_remove] = 0;
        i++;
      }
      else if(!strcmp(argv[i], "remove_table"))
      {
        remove_table(table);
      }
      else if(!strcmp(argv[i], "wartosc"))
      {
        for(int j = 0; j < atoi(argv[i+1]); j++)
        {
          exec_search(argv[i-5], argv[i-4], argv[i-3]);
          index_number = write_block(table, table_size, argv[i-3]);
          //index_number++;
          remove_block(table, index_number);
        }
        i++;
      }
      else return 1;
      i++;
    }

    end_clock(tmp);

  #endif


  #ifndef DLL

  start_clock();

  while(i < argc)
  {
    if(!strcmp(argv[i], "create_table"))
    {
      table_size = atoi(argv[i+1]);
      table = new_table(table_size);
      i++;
    }
    else if(!strcmp(argv[i], "search"))
    {
      exec_search(argv[i+1], argv[i+2], argv[i+3]);
      index[index_number] = write_block(table, table_size, argv[i+3]);
      index_number++;
      i+=3;
    }
    else if(!strcmp(argv[i], "remove_block"))
    {
      int index_to_remove = atoi(argv[i+1]);
      remove_block(table, index_to_remove);
      index[index_to_remove] = 0;
      i++;
    }
    else if(!strcmp(argv[i], "remove_table"))
    {
      remove_table(table);
    }
    else if(!strcmp(argv[i], "wartosc"))
    {
      for(int j = 0; j < atoi(argv[i+1]); j++)
      {
        exec_search(argv[i-5], argv[i-4], argv[i-3]);
        index_number = write_block(table, table_size, argv[i-3]);
        //index_number++;
        remove_block(table, index_number);
      }
      i++;
    }
    else return 1;
    i++;
  }

  end_clock(tmp);
  #endif

  fclose(tmp);


  #ifdef DLL
    dlclose(dll);
  #endif

  return 0;
}

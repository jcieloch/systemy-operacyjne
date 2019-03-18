#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <inttypes.h>

clock_t st_time;
clock_t en_time;
struct tms st_cpu;
struct tms en_cpu;

void start_clock()
{
    st_time = times(&st_cpu);
}

void end_clock(FILE *destFile)
{
    en_time = times(&en_cpu);
    char buffer[1000] = {0};
    sprintf(buffer, "User Time: %jd, System Time: %jd\n\n",
        //(intmax_t)(en_time - st_time),
        (intmax_t)(en_cpu.tms_utime - st_cpu.tms_utime),// / CLOCKS_PER_SEC,
        (intmax_t)(en_cpu.tms_stime - st_cpu.tms_stime));// / CLOCKS_PER_SEC);
    fputs(buffer, destFile);
}

void generate(char* file_name, int size, int record_size)
{
  char** tab = (char**)malloc(size*sizeof(char*));
  FILE* f = fopen(file_name, "w+");
  for(int i=0; i<size; i++)
  {
    tab[i] = (char*)malloc(record_size*sizeof(char));
    for(int j=0; j<record_size; j++)
    {
       char randomletter = 'A' + (rand() % 26);
       tab[i][j] = randomletter;
    }
    fwrite(tab[i], sizeof(char), record_size, f);
    fwrite("\n", sizeof(char), 1, f);
  }
  for(int i=0; i<size; i++)
  {
    free(tab[i]);
  }
  free(tab);
  fclose(f);
}

char* lib_get_record(FILE* file, int record_size, int index)
{
  char* new_record = (char*)malloc(record_size*sizeof(char));
  fseek(file, (record_size+1)*index, 0); //+ \n
  fread(new_record, sizeof(char), record_size, file);
  return new_record;
}
void lib_insert_record(FILE* file, int record_size, int index, char* new_record)
{
  fseek(file, (record_size+1)*index, 0);
  fwrite(new_record, sizeof(char), record_size, file);
}
void lib_sort(char* file_name, int size, int record_size)
{
  FILE* file = fopen(file_name, "r+");
  if(file == NULL)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  for(int i=0; i<size; i++)
  {
    char* min_record = lib_get_record(file, record_size, i);
    int min_index = i;
    char min_char = min_record[0];
    for(int j=i+1; j<size; j++)
    {
      char* tmp = lib_get_record(file, record_size, j);
      if((int)tmp[0] < (int)min_char)
      {
        min_index = j;
        min_char = tmp[0];
      }
      free(tmp);
    }
    if(min_index != i)
    {
      char* tmp = lib_get_record(file, record_size, min_index);
      lib_insert_record(file, record_size, i, tmp);
      lib_insert_record(file, record_size, min_index, min_record);
      free(tmp);
    }
    free(min_record);
  }
  fclose(file);
}

char* sys_get_record(int file, int record_size, int index)
{
  lseek(file, (record_size+1)*index, SEEK_SET); //liczac od poczatku, znak konca linii
  char* content = (char*)malloc(record_size*sizeof(char));
  read(file, content, record_size);
  return content;
}
void sys_insert_record(int file, int record_size, int index, char* new_record)
{
  lseek(file, (record_size+1)*index, SEEK_SET);
  write(file, new_record, record_size);
}
void sys_sort(char* file_name, int size, int record_size)
{
  int file = open(file_name, O_RDWR);
  if(file < 0)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  for(int i=0; i<size; i++)
  {
    char* min_record = sys_get_record(file, record_size, i);
    int min_index = i;
    char min_char = min_record[0];
    for(int j=i+1; j<size; j++)
    {
      char* tmp = sys_get_record(file, record_size, j);
      if((int)tmp[0] < (int)min_char)
      {
        min_index = j;
        min_char = tmp[0];
      }
      free(tmp);
    }
    if(min_index != i)
    {
      char* tmp = sys_get_record(file, record_size, min_index);
      sys_insert_record(file, record_size, i, tmp);
      sys_insert_record(file, record_size, min_index, min_record);
      free(tmp);
    }
    free(min_record);
  }
  close(file);
}

void lib_copy(char* file1, char* file2, int records_to_copy, int buff_size)
{
  FILE* from = fopen(file1, "r");
  if(from == NULL)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  FILE* to = fopen(file2, "w");
  if(to == NULL)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  char* bufor = (char*)malloc(buff_size*sizeof(char));
  int i = 0;
  buff_size++;  // '\n'
  while(i<records_to_copy)
  {
    fread(bufor, sizeof(char), buff_size, from);
    if(feof(from)) break;
    if(strchr(bufor, '\n') != NULL) i++;
    fwrite(bufor, sizeof(char), buff_size, to);
  }
  free(bufor);
  fclose(from);
  fclose(to);
}

void sys_copy(char* file1, char* file2, int records_to_copy, int buff_size)
{
  int from = open(file1, O_RDONLY);
  if(from < 0)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  int to = open(file2, O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
  if(to < 0)
  {
    printf("Blad przy otwieraniu pliku\n");
  }
  char* bufor = (char*)malloc(buff_size*sizeof(char));
  int i = 0;
  buff_size++;  // '\n'
  while(i<records_to_copy)
  {
    if(read(from, bufor, buff_size) == 0) break;
    if(strchr(bufor, '\n') != NULL) i++;
    write(to, bufor, buff_size);
  }
  free(bufor);
  close(from);
  close(to);
}
void remove_table(char** tab, int size, int record_size)
{
  for(int i=0; i<size; i++)
  {
    free(tab[i]);
  }
  free(tab);
}

int main(int args, char* argv[])
{
  srand(time(NULL));
  int size;
  int record_size;
  char* file_name;

  FILE * tmp = NULL;
  char* results = "wyniki.txt";
  tmp = fopen(results, "a");

  if(args < 2)
  {
    printf("Za malo argumentow\n");
  }
  if(!strcmp(argv[1], "generate"))
  {
    size = atoi(argv[3]);
    record_size = atoi(argv[4]);
    file_name = argv[2];
    generate(file_name, size, record_size);
  }

  start_clock();
  if(!strcmp(argv[1], "sort"))
  {
    size = atoi(argv[3]);
    record_size = atoi(argv[4]);
    file_name = argv[2];
    char* func_type = argv[5];
    if(!strcmp(func_type, "sys"))
    {
      sys_sort(file_name, size, record_size);
    }
    else if(!strcmp(func_type, "lib"))
    {
      lib_sort(file_name, size, record_size);
    }
  }
  if(!strcmp(argv[1], "copy"))
  {
    int records_to_copy = atoi(argv[4]);
    int bufor_size = atoi(argv[5]);
    char* file_name1 = argv[2];
    char* file_name2 = argv[3];
    char* func_type = argv[6];
    if(!strcmp(func_type, "sys"))
    {
      sys_copy(file_name1, file_name2, records_to_copy, bufor_size);
    }
    else if(!strcmp(func_type, "lib"))
    {
      lib_copy(file_name1, file_name2, records_to_copy, bufor_size);
    }
  }
  end_clock(tmp);
  fclose(tmp);
  return 0;
}

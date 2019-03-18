#define _XOPEN_SOURCE 500
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>
#define __USE_BSD
//#define __USE_XOPEN
#include <time.h>
#include <ftw.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>

const char format[] = "%Y-%m-%d %H:%M:%S";
char buffer[100];
time_t date_nftw;
char* op;

double date_compare(time_t date_1, time_t date_2) {
    return difftime(date_1, date_2);
}

void print_infos(char* path, struct stat* fileStat, char* file_name)
{
  //http://codewiki.wikidot.com/c:system-calls:stat
  printf("%s\n", path);
  printf("File Size: \t\t%ld bytes\n",fileStat->st_size);
  if(S_ISREG(fileStat->st_mode))  printf("The file is a regular file\n");
  if(S_ISDIR(fileStat->st_mode)) printf("The file is a directory\n");
  if(S_ISLNK(fileStat->st_mode)) printf("The file is a symbolic link\n");
  if(S_ISBLK(fileStat->st_mode)) printf("The file is a block file\n");
  if(S_ISCHR(fileStat->st_mode)) printf("The file is a character file\n");
  if(S_ISFIFO(fileStat->st_mode)) printf("The file is a fifo file\n");
  strftime(buffer, 100, format, localtime(&fileStat->st_mtime));    //modyfikacji
  printf("Czas modyfikacji %s\n", buffer);
  strftime(buffer, 100, format, localtime(&fileStat->st_atime));    //dostepu
  printf("Czas dostepu %s\n", buffer);
  printf("\n\n");

}

static int nftw_print(const char *dirpath, const struct stat* fileStat, int flag, struct FTW *ftwbuf)
{
  if(strcmp(op, "=") && date_compare(date_nftw, fileStat->st_mtime) == 0)
  {
    printf("%s\n", dirpath);
    printf("File Size: \t\t%ld bytes\n",fileStat->st_size);
    if(S_ISREG(fileStat->st_mode))  printf("The file is a regular file\n");
    if(S_ISDIR(fileStat->st_mode)) printf("The file is a directory\n");
    if(S_ISLNK(fileStat->st_mode)) printf("The file is a symbolic link\n");
    if(S_ISBLK(fileStat->st_mode)) printf("The file is a block file\n");
    if(S_ISCHR(fileStat->st_mode)) printf("The file is a character file\n");
    if(S_ISFIFO(fileStat->st_mode)) printf("The file is a fifo file\n");
    strftime(buffer, 100, format, localtime(&fileStat->st_mtime));    //modyfikacji
    printf("Czas modyfikacji %s\n", buffer);
    strftime(buffer, 100, format, localtime(&fileStat->st_atime));    //dostepu
    printf("Czas dostepu %s\n", buffer);
    printf("\n\n");
  }
  if(strcmp(op, "<") && date_compare(date_nftw, fileStat->st_mtime) < 0)
  {
    printf("%s\n", dirpath);
    printf("File Size: \t\t%ld bytes\n",fileStat->st_size);
    if(S_ISREG(fileStat->st_mode))  printf("The file is a regular file\n");
    if(S_ISDIR(fileStat->st_mode)) printf("The file is a directory\n");
    if(S_ISLNK(fileStat->st_mode)) printf("The file is a symbolic link\n");
    if(S_ISBLK(fileStat->st_mode)) printf("The file is a block file\n");
    if(S_ISCHR(fileStat->st_mode)) printf("The file is a character file\n");
    if(S_ISFIFO(fileStat->st_mode)) printf("The file is a fifo file\n");
    strftime(buffer, 100, format, localtime(&fileStat->st_mtime));    //modyfikacji
    printf("Czas modyfikacji %s\n", buffer);
    strftime(buffer, 100, format, localtime(&fileStat->st_atime));    //dostepu
    printf("Czas dostepu %s\n", buffer);
    printf("\n\n");
  }
  if(strcmp(op, ">") && date_compare(date_nftw, fileStat->st_mtime) > 0)
  {
    printf("%s\n", dirpath);
    printf("File Size: \t\t%ld bytes\n",fileStat->st_size);
    if(S_ISREG(fileStat->st_mode))  printf("The file is a regular file\n");
    if(S_ISDIR(fileStat->st_mode)) printf("The file is a directory\n");
    if(S_ISLNK(fileStat->st_mode)) printf("The file is a symbolic link\n");
    if(S_ISBLK(fileStat->st_mode)) printf("The file is a block file\n");
    if(S_ISCHR(fileStat->st_mode)) printf("The file is a character file\n");
    if(S_ISFIFO(fileStat->st_mode)) printf("The file is a fifo file\n");
    strftime(buffer, 100, format, localtime(&fileStat->st_mtime));    //modyfikacji
    printf("Czas modyfikacji %s\n", buffer);
    strftime(buffer, 100, format, localtime(&fileStat->st_atime));    //dostepu
    printf("Czas dostepu %s\n", buffer);
    printf("\n\n");
  }
  return 0;
}
void find_for_files(char* path, char* compare_sign, time_t date)
{
  DIR* d = opendir(path);
  if(d == NULL) return;
  struct dirent* file;
  rewinddir(d);
  file = readdir(d);
  struct stat buff;
  while(file != NULL)
  {

    char new_path[100] = {0};
    strcpy(new_path, path);
    strcat(new_path, "/");
    strcat(new_path, file->d_name);
    lstat(file->d_name, &buff);
    if(strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0)
    {
      file = readdir(d);
      continue;
    }
    else
    {
      if(strcmp(compare_sign, "=") && date_compare(date, buff.st_mtime) == 0)
      {
        print_infos(new_path, &buff, file->d_name);
      }
      else if (strcmp(compare_sign, "<") && date_compare(date, buff.st_mtime) < 0)
      {
        print_infos(new_path, &buff, file->d_name);
      }
      else if (strcmp(compare_sign, ">") && date_compare(date, buff.st_mtime) > 0)
      {
        print_infos(new_path, &buff, file->d_name);
      }
      if(S_ISDIR(buff.st_mode)) find_for_files(new_path, compare_sign, date);
      file = readdir(d);
    }
  }
  closedir(d);
}

void find_for_files_with_nftw(char* path, char* compare_sign, time_t date)
{
  nftw(path, nftw_print, 100, FTW_PHYS);
}

int main(int args, char* argv[])
{
  if(args < 4)
  {
    printf("Za malo argumentow\n");
    return 1;
  }
  char* path = argv[1];
  char* comp_sign = argv[2];
  char* dat = argv[3];
  //char* usr_date = "2019-03-18 20:40:00";
  struct tm *timestamp = malloc(sizeof(struct tm));
  strptime(dat, format, timestamp);
  time_t date = mktime(timestamp);
  date_nftw = date;
  op = comp_sign;
  if(args == 5) find_for_files_with_nftw(path, comp_sign, date);
  else find_for_files(path, op, date_nftw);
  return 0;
}

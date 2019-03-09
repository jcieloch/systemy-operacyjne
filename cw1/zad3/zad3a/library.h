

typedef struct
{
  char* catalog_name;
  char* file_name;
} searching_parameters;

char** new_table(int size);

searching_parameters actual_search(char* catalog_name, char* file_name);

int exec_search(char* catalog_name, char* file_name, char* tmp_file_name);

int write_block(char** table, int table_size, char* tmp_file_name);

int remove_block(char** table, int index);

int remove_table(char** table);


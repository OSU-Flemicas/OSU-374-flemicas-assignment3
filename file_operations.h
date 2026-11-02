#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

typedef enum LOOKUP_TYPE{
    LARGEST,
    SMALLEST,
} lookup;

void make_directory(char **directory_name);
void make_file_path(char **file_path, char *directory_name, int year);
void write_file(char *file_path, char *write_string);
void find_file(char **file_path, lookup type);
int check_file_exists(char **file_path);

#endif
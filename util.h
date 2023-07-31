#ifndef UTIL_H_
#define UTIL_H_

char * substring(int start, int end, char string[]);
char ** str_split(char string[], char delimiter);
char ** multi_str_split(char string[], char delimiter, size_t *size);
int get_delimiter(char string[], char delimiter, int * del_buffer);
void char_replace(char string[], char find, char replace);
void free_array(char ** arr_str, size_t arr_size);

#endif
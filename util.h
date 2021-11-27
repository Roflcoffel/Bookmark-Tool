#ifndef UTIL_H_
#define UTIL_H_

char * substring(int start, int end, char string[]);
char ** str_split(char string[], char delimiter);
char ** multi_str_split(char string[], char delimiter, size_t *size);
int count_delimiter(char string[], char delimiter);
void char_replace(char string[], char find, char replace);
void free_array(char ** arr_str, size_t arr_size);

#endif
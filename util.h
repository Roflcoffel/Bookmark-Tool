#ifndef UTIL_H_
#define UTIL_H_

char * substring(int start, int end, char string[S_SIZE]);
char ** str_split(char string[S_SIZE], char delimiter);
char ** multi_str_split(char string[S_SIZE], char delimiter, size_t *size);
int count_delimiter(char string[S_SIZE], char delimiter);
char * char_replace(char string[S_SIZE], char delimiter, char new_delimiter);

#endif
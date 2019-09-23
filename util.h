#ifndef UTIL_H_
#define UTIL_H_

#define MAX_SIZE 255

char * substring(int start, int end, char string[MAX_SIZE]);
char ** str_split(char string[MAX_SIZE], char delimiter);

#endif
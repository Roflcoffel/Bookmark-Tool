//Hopefully useful functions
#include "util.h"

char * substring(int start, int end, char string[MAX_SIZE])
{
        char *substring[MAX_SIZE];
        int tmp;

        if(start > MAX_SIZE) return string;
        if(end > MAX_SIZE) end = MAX_SIZE;
        if(start > end)
        {
                tmp = start;
                start = end;
                end = tmp;        
        }

        for(int i = start; i < end; i++)
        {
                substring[i] = string[i];
        }
        
        return substring;
}

//Returns an array with two strings
char ** str_split(char string[MAX_SIZE], char delimiter)
{
        char str[2][MAX_SIZE];
        int len = strlen(string);
        strcpy(str[0], string);

        for(int i = 0; i < len; i++)
        {
                if(string[i] == delimiter) {
                        strcpy(str[0], substring(0,i-1,string));
                        strcpy(str[1], substring(i+1,len,string));
                        break;
                }
        }

        return str;
}
//Hopefully useful functions
#include "util.h"
#include <string.h>
#include <stdlib.h>

//Creates a substring from a string adds a null character
//start       - array start index
//num_of_char - number of total characters, 0 == length of "string";
//string      - string to extract from
char * substring(int start, int num_of_char, char string[MAX_SIZE])
{       
        if(start > MAX_SIZE) return string;

        num_of_char += start;

        if(num_of_char == 0)       num_of_char = strlen(string);
        if(num_of_char > MAX_SIZE) num_of_char = MAX_SIZE-1;

        char * substring = malloc(MAX_SIZE * sizeof(char));

        for(int i = start; i < num_of_char; i++)
        {
                substring[i] = string[i];
        }

        substring[num_of_char] = '\0';
        
        return substring;
}

//Returns an array with two strings
char ** str_split(char string[MAX_SIZE], char delimiter)
{
        char ** str = malloc(2 * sizeof(char*));
        int len = strlen(string);

        str[0] = malloc(MAX_SIZE * sizeof(char));
        str[1] = malloc(MAX_SIZE * sizeof(char));

        for(int i = 0; i < len; i++)
        {
                if(string[i] == delimiter) 
                {
                        strcpy(str[0], substring(0,i-1,string));
                        strcpy(str[1], substring(i+1,0,string));
                        break;
                }
        }

        return str;
}
//Hopefully useful functions
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h> //for printf debugging for now

#include "util.h"
//Creates a substring from a string adds a null character
//start       - array start index
//num_of_char - number of total characters, 0 == length of "string";
//string      - string to extract from
//return      - a substring
char * substring(int start, int num_of_char, char string[MAX_SIZE])
{       
        if(start > MAX_SIZE) return string;

        num_of_char += start;

        if(num_of_char-start == 0) num_of_char = strlen(string);
        if(num_of_char > MAX_SIZE) num_of_char = MAX_SIZE-1;

        char * substring = malloc(MAX_SIZE * sizeof(char));

        for(int i = start; i < num_of_char; i++)
        {
                substring[i-start] = string[i];
        }

        substring[num_of_char] = '\0';

        return substring;
}

//Splits a string at a delimiter in two
//string    - string you want to split
//delimiter - the character to split at
//return    - an array with two strings
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
                        strcpy(str[0], substring(0,i,string));
                        strcpy(str[1], substring(i+1,0,string));
                        break;
                }
        }

        return str;
}

//Splits a string at ALL delimiters
//strings starting or ending with a space are not supported!
//string    - string you want to split
//delimiter - the character you want to split at, if the delimiter is not found returns the input in a char **
//size      - stores the array size in this variable (output)
//returns   - an array of strings
char ** multi_str_split(char string[MAX_SIZE], char delimiter, size_t *size)
{
        size_t len = strlen(string);
        
        int array_size = count_delimiter(string, delimiter);

        char ** str = malloc((array_size+1) * sizeof(char*));
        //char * str[array_size+1]; test this
        //char str[array_size+1][MAX_SIZE]; test this
        //see if all of these work the same way
        
        *size = array_size+1;

        if(array_size == 0)
        {
                str[0] = malloc(MAX_SIZE * sizeof(char));
                strcpy(str[0], string);
                return str;
        }

        int count = 0;
        int start = 0;
        for(int i = 0; i < len+1; i++)
        {
                if(string[i] == delimiter || i == len)
                {
                        str[count] = malloc(MAX_SIZE * sizeof(char));
                        strcpy(str[count], substring(start,i-start,string));
                        start = i+1;
                        count++;
                }
        }

        return str;
}

//Counts the delimiters in a string
//string     - string to count delimiters in
//delimiter  - the character you want to count
//returns    - a count of delimiters
int count_delimiter(char string[MAX_SIZE], char delimiter)
{
        int count_delimiter = 0;
        size_t len = strlen(string);

        //Skips first and last character
        for(int i = 1; i < len-1; i++)
        {
                if(string[i] == delimiter)
                {
                        count_delimiter++;
                }
        }

        return count_delimiter;
}
//Hopefully useful functions
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "size.h"
#include "util.h"
//Creates a substring from a string adds a null character
//start       - array start index
//num_of_char - number of total characters, 0 == length of "string";
//string      - string to extract from
//return      - a substring
char * substring(int start, int num_of_char, char string[S_SIZE])
{       
        if(start > S_SIZE) return string;

        num_of_char += start;

        if(num_of_char-start == 0) num_of_char = strlen(string);
        if(num_of_char > S_SIZE) num_of_char = S_SIZE-1;

        char * substring = malloc(S_SIZE * sizeof(char));

        for(int i = start; i < num_of_char; i++)
        {
                substring[i-start] = string[i];
        }

        substring[num_of_char] = '\0';

        return substring;
}

//Splits a string at a delimiter in two
//string    - string you want to split
//delimiter - the character to split at, if a delimter is not found returns the input in char **
//return    - an array with two strings
char ** str_split(char string[S_SIZE], char delimiter)
{
        char ** str = malloc(2 * sizeof(char*));
        int len = strlen(string);

        str[0] = malloc(S_SIZE * sizeof(char));
        str[1] = malloc(S_SIZE * sizeof(char));

        bool delimter_found = false;

        for(int i = 0; i < len; i++)
        {
                if(string[i] == delimiter) 
                {
                        delimter_found = true;
                        strcpy(str[0], substring(0,i,string));
                        strcpy(str[1], substring(i+1,0,string));
                        break;
                }
        }

        if(delimter_found == false) strcpy(str[0], string);

        return str;
}

//Splits a string at ALL delimiters
//strings starting or ending with a delimiter are not supported!
//string    - string you want to split
//delimiter - the character you want to split at, if the delimiter is not found returns the input in a char **
//size      - stores the array size in this variable (output)
//returns   - an array of strings
char ** multi_str_split(char string[S_SIZE], char delimiter, size_t *size)
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
                str[0] = malloc(S_SIZE * sizeof(char));
                strcpy(str[0], string);
                return str;
        }

        int count = 0;
        int start = (string[0] == delimiter) ? 1 : 0; //Skip if first char is a /
        for(int i = 1; i < len+1; i++)
        {
                if(string[i] == delimiter || i == len)
                {
                        str[count] = malloc(S_SIZE * sizeof(char));
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
int count_delimiter(char string[S_SIZE], char delimiter)
{
        int count_delimiter = 0;
        size_t len = strlen(string);

        //Skips first and last character
        for(int i = 1; i < len; i++)
        {
                if(string[i] == delimiter)
                {
                        count_delimiter++;
                }
        }

        return count_delimiter;
}

//finds and replaces all delimters in a string with the new_delimiter
//string        - the input string that will be modified
//find          - current delimiter, will be replaced
//replace       - the new delimiter
void char_replace(char string[S_SIZE], char find, char replace)
{
        size_t len = strlen(string);

        for (int i = 0; i < len; i++)
        {
                if(string[i] == find)
                {
                        string[i] = replace;
                }
        }
}

//frees a char ** (string array), from memory
//arr_str  - input arr_str to free from memory.
//arr_size - the size of the arr_str 
void free_array(char ** arr_str, size_t arr_size)
{
        for (int i = 0; i < arr_size; i++)
        {
                free(arr_str[i]);
        }
}
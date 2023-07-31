//Hopefully useful functions
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h> //JUST FOR PRINTF

#include "util.h"
//Creates a substring from a string adds a null character
//start       - array start index
//num_of_char - number of total characters, 0 == length of "string";
//string      - string to extract from
//return      - a substring (a malloced block)
char * substring(int start, int num_of_char, char string[])
{
        int len = strlen(string);
        if(start > len) return string;

        num_of_char += start;

        if(num_of_char-start == 0) num_of_char = len;
        if(num_of_char > len)      num_of_char = len;

        char * substring = malloc(len * sizeof(char));

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
char ** str_split(char string[], char delimiter)
{
        char ** str = malloc(2 * sizeof(char*));
        int len = strlen(string);

        str[0] = malloc(len * sizeof(char));
        str[1] = malloc(len * sizeof(char));

        bool delimter_found = false;

        for(int i = 0; i < len; i++)
        {
                if(string[i] == delimiter) 
                {
                        delimter_found = true;
                        
                        char * element0 = substring(0,i,string);
                        char * element1 = substring(i+1,0,string);

                        strcpy(str[0], element0);
                        strcpy(str[1], element1);

                        free(element0); free(element1);
                        break;
                }
        }

        if(delimter_found == false) strcpy(str[0], string);

        return str;
}


//RETEST THIS FUNCTION!!!!!!
//Splits a string at ALL delimiters
//strings starting or ending with a delimiter are not supported!
//string    - string you want to split
//delimiter - the character you want to split at, if the delimiter is not found returns the input in a char **
//size      - stores the array size in this variable (output)
//returns   - an array of strings, (malloced block)
char ** multi_str_split(char string[], char delimiter, size_t *size)
{
        int len = strlen(string);

        // We ignore starting and ending delimiters.
        // This means that the amount of words in a string is always delimters+1
        int del_indexes[len-2];
        int array_size = get_delimiter(string, delimiter, del_indexes) + 1;

        //Should now contain the position of each delimiter and the null character.
        del_indexes[array_size-1] = len+1;

        char ** str = malloc((array_size) * sizeof(char*)); 
        
        *size = array_size;

        if(array_size == 0)
        {
                str[0] = malloc(len * sizeof(char));
                strcpy(str[0], string);
                return str;
        }

        int start = (string[0] == delimiter) ? 1 : 0; //Skip if first char is a "delimiter"
        for(int i = 0; i < array_size; i++)
        {
                str[i] = malloc(len * sizeof(char));
                char * part = substring(start,del_indexes[i]-start,string);
                strcpy(str[i], part);
                start = del_indexes[i]+1;
                free(part);
        }

        return str;
}

//Gets the positions of all delimiters in a string.
//Skips the first and the last character
//string     - string to get delimiters from.
//delimiter  - the character you want to find.
//del_buffer - an array with all the indexes of the delimiters.
//returns    - the number of delimiters
int get_delimiter(char string[], char delimiter, int * del_buffer)
{
        int len = strlen(string);
        int count = 0;

        //Skips first and last character
        for(int i = 1; i < len; i++)
        {
                if(string[i] == delimiter)
                {
                        del_buffer[count] = i;
                        count++;
                }
        }

        return count;
}

//finds and replaces all delimters in a string with the new_delimiter
//string        - the input string that will be modified
//find          - current delimiter, will be replaced
//replace       - the new delimiter
void char_replace(char string[], char find, char replace)
{
        int len = strlen(string);

        for (int i = 0; i < len; i++)
        {
                if(string[i] == find)
                {
                        string[i] = replace;
                }
        }
}

//frees the elements of a char ** array.
//arr_str  - input arr_str to free from memory.
//arr_size - the size of the arr_str 
void free_array(char ** arr_str, size_t arr_size)
{
        for (int i = 0; i < arr_size; i++)
        {
                free(arr_str[i]);
        }
}
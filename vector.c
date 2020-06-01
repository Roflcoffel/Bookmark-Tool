//Simple vector for dicts.
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "size.h"
#include "vector.h"
#include "util.h"

//an "empty" dict; Constructor
Dict dict_new(char key[S_SIZE], int value)
{
        Dict new;
        strcpy(new.key, key);
        new.value = value;

        return new;
}

//Constructor
Vector vector_new(void)
{
        Vector vect;
        vect.size = 0; //Acts as an index. / max size
        vect.capacity = INITAL_VECTOR_SIZE;
        vect.data = malloc(sizeof(Dict) * vect.capacity);
        
        //terminate program if malloc can't alocate memory.
        assert(vect.data != NULL);

        return vect;
}

void vector_add(Dict dict, Vector *vect)
{
        if(vect->size >= vect->capacity) {
                vect->capacity *= 2;
                vect->data = realloc(vect->data, sizeof(Dict) * vect->capacity);

                //terminate program if realloc can't alocate memory.
                assert(vect->data != NULL);
        }
        vect->data[vect->size++] = dict;
}

//Returns all item that matches the key, or matches atleast 2 letters.
//the 2 letter matches, string must be the same length as the key (may change).
Vector vector_match(char key[S_SIZE], Vector vect)
{       
	Vector new_vect = vector_new();
        int matches[vect.size];

        int key_len = strlen(key);
        bool full_match_found = false;

        //Counts each matching character, and stores the number of matches.
        for(int i = 0; i < vect.size; i++)
        {
                size_t size = 0;
                char ** split_vect = multi_str_split(vect.data[i].key, ' ', &size);

                int num_matches = 0;
                
                for(int j = 0; j < size; j++)
                {
                        int len = strlen(split_vect[j]);
                        if(len != key_len) continue;
                        
                        for(int k = 0; k < len; k++)
                        {
                                if(tolower(split_vect[j][k]) != tolower(key[k])) break;

                                num_matches++;

                                //Full Match
                                if(k == len-1) {
                                        vector_add(vect.data[i], &new_vect);
                                        full_match_found = true;
                                }
                        }
                }

                matches[i] = num_matches;
                free(split_vect);
        }

        //Didn't find a full match, see if we any 2 letter matches.
        if(full_match_found == false)
        {
                for (int i = 0; i < vect.size; i++)
                {
                        if(matches[i] >= 2) vector_add(vect.data[i], &new_vect);
                }

                if(new_vect.size == 0) vector_add(dict_new("No Match Found", 0), &new_vect);
        }

        return new_vect;
}

int vector_find_index(char key[S_SIZE], Vector vect)
{
        for(int i = 0; i < vect.size; i++)
        {
                if(strcasecmp(vect.data[i].key,key) == 0) {
                        return i;
                }      
        }
        return -1; //No index was found
}

Dict vector_find_by_index(int index, Vector vect)
{
        return vect.data[index];
}

//find the specified key; NULL object if not found
//requires an exact key, so it is not user friendly.
Dict vector_find(char key[S_SIZE], Vector vect)
{
        int index = vector_find_index(key, vect);
        if(index == -1)
                return dict_new("NULL", 0);
        
        return vector_find_by_index(index, vect);
}

void vector_inc(int index, Vector *vect)
{
        vect->data[index].value++;
}

//Sets the key and value to NULL and 0
void vector_remove(char key[S_SIZE], Vector *vect)
{
        int index = vector_find_index(key, *vect);
        vect->data[index] = dict_new("NULL", 0);
}

void vector_destroy(Vector *vect)
{
        free(vect->data);
        vect = NULL;
}


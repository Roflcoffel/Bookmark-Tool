//Simple vector for dicts.
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

//Returns 1 item if it matches all letters, if not
//Returns all item that matches atleast 2 letters.
//If more than one matches all, returns the first found
//Current problem:
//if a series only have common words, like "love" then
//it is not guarenteed that the first instance "love" is
//the one we want.
//so to fix this we have to allow, on a full match we still check the rest
//and return a vector.
//currently we discard if the length of the strings do not match, can create
//a test and see how much slower it is to always check all.
Vector vector_match(char key[S_SIZE], Vector vect)
{       
	Vector new_vect = vector_new();
        int matches[vect.size]; //may need sizeof(int) * vect.size?

        int key_len = strlen(key);

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
			                return new_vect;
                                }
                        }
                }

                matches[i] = num_matches;
        }

        for (int i = 0; i < vect.size; i++)
        {
                //Matches atleast two letters
                if(matches[i] >= 2) vector_add(vect.data[i], &new_vect);
        }

        if(vect.size == 0)
        {
                vector_add(dict_new("No Match Found", 0), &new_vect);
                return new_vect;
        }

        return new_vect;
}

int vector_find_index(char key[S_SIZE], Vector vect)
{
        for(int i = 0; i < vect.size; i++)
        {
                if(strcmp(vect.data[i].key,key) == 0) {
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


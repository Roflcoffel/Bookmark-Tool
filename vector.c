//Simple vector for dicts.
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "vector.h"

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

//Returns 1 item if it matches all 4 letters, if not
//Returns all item that matches atleast 2 letters.
//try to cut each key string at a "space" symbol
//and for each new string match the first 4 characters.
//so for "the rising shield hero" you can search
//the, rising, shield and hero.
Vector vector_match(char key[S_SIZE], Vector vect)
{
		Vector new_vect = vector_new();
        int max_match = 4;
        int matches[vect.size]; //may need sizeof(int) * vect.size?

        //Counts each matching character, and stores the number of matches.
        for(int i = 0; i < vect.size; i++)
        {
                int num_matches = 0;
                
                for(int j = 0; j <= max_match; j++)
                {
                        if(tolower(vect.data[i].key[j]) != tolower(key[j])) {
                                break;
                        }

                        num_matches++;

                        if(j == max_match) {
                        	vector_add(vect.data[i], &new_vect);
							return new_vect;
						}
                }

                matches[i] = num_matches;
        }

		for (int i = 0; i < vect.size; i++)
		{
			if(matches[i] >= 2) vector_add(vect.data[i], &new_vect);
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


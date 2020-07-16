//Simple vector for dicts.
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "size.h"
#include "vector.h"
#include "util.h"

//Constructor
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

//finds all items that matches atleast 2 letters.
//key    - search term
//vect   - where your search term will be used.
//return - all item that matches the key, or matches atleast 2 letters.
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
                free_array(split_vect, size); free(split_vect);
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

//finds the index of the provided key, in a vector
//key     - search term, (needs to match all character)
//vect    - where your search term will be used.
//return  - the index of a match
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

//find the specified key; NULL object if not found
//requires an exact key, so it is not user friendly.
//key    - search term, (needs to match all character)
//vect   - where your search term will be used.
//index  - (output) also gives you the index of your search term, if found.
//return - a dict of your match
Dict vector_find(char key[S_SIZE], Vector vect, int *index)
{
        *index = vector_find_index(key, vect);
        if(*index == -1)
                return dict_new("NULL", 0);
        
        return vect.data[*index];
}

//Counts the char in each key and returns the longest
//vect   - the vector to search through
//return - lenght of the longest key
int vector_longest_key(Vector vect)
{
        int cur_longest = 0;
        int length = 0;
        for (size_t i = 0; i < vect.size; i++)
        {
                for (length = 0; vect.data[i].key[length] != '\0'; length++)
                
                if(length > cur_longest)
                        cur_longest = length;
        }
        
        return cur_longest;
}

void vector_inc(int index, Vector *vect)
{
        vect->data[index].value++;
}

void vector_remove(int index, Vector *vect)
{
        vect->data[index] = dict_new("NULL", 0);
}

void vector_destroy(Vector *vect)
{
        free(vect->data);
}

bool valid_id(int index, Vector db)
{
        return index <= db.size && index >= 0 ? true : false;
}
//Simple vector for dicts.
#define S_SIZE 255
#define DICT_SIZE 255
#define INITAL_VECTOR_SIZE 2

#include <ctype.h>
#include "vector.h"

Type type_new_s(char string[S_SIZE])
{
        Type t;
        strcpy(t.STR, string);
        return t;
}

Type type_new_i(int integer)
{
        Type t;
        t.INT = integer;
        return t;
}

//an "empty" dict; Constructor
Dict dict_new(char key[S_SIZE], Type value)
{
        Dict new;
        strcpy(new.key, key);
        new.value = value;

        return new;
}

//Constructor
Vector vector_new(void)
{
        Vector v;
        v.size = 0;
        v.capacity = INITAL_VECTOR_SIZE;
        v.data = malloc(sizeof(Dict) * v.capacity);
        
        return v;
}

void vector_add(Dict dict, Vector *vect)
{
        if(vect->size >= vect->capacity) {
                vect->capacity *= 2;
                vect->data = realloc(vect->data, sizeof(Dict) * vect->capacity);
        }
        vect->data[vect->size++] = dict;
}

//find the specified key; NULL object if not found
Dict vector_find(char key[S_SIZE], Vector vect)
{
        for(int i = 0; i < vect.size; i++)
        {
                if(strcmp(vect.data[i].key, key) == 0)
                        return vect.data[i];
        }
        return dict_new("NULL", type_new_i(0));
}

//finds the best match;
Dict vector_match(char key[S_SIZE], Vector vect)
{
        int max_match = 4;
        int matches[vect.size];

        for(int i = 0; i < vect.size; i++)
        {
                int cur_matches = 0;
                
                for(int j = 0; j <= max_match; j++)
                {
                        if(toLower(vect.data[i].key[j]) != toLower(key[j])) {
                                break;
                        }
                        
                        cur_matches++;

                        if(j == max_match) {
                                return vect.data[i];
                        }
                }

                matches[i] = cur_matches;
        }

        int max = matches[0];
        int best_match_index = 0;

        for(int i = 0; i < vect.size; i++)
        {
                if(matches[i] > max) {
                        best_match_index = i;
                        max = matches[i];
                }        
        }
        
        return vect.data[best_match_index];
}

int vector_find_index(char key[S_SIZE], Vector vect)
{
        for(int i = 0; i < vect.size; i++)
        {
                if(strcmp(vect.data[i].key,key) == 0) {
                        return i;
                }      
        }
        printf("Index not found!\n");
        return -1;
}

void vector_remove(char key[S_SIZE], Vector *vect)
{
        int index = vector_find_index(key, *vect);
        vect->data[index] = dict_new("NULL", type_new_i(0));
}

void vector_destroy(Vector *vect)
{
        free(vect->data);
}


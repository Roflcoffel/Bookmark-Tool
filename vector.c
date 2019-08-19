//Simple vector for dicts.
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
//NOTE: right now only matches the first 4 letters
//which would make searching for the rising... you
//need to write "the" which also probably matches something else.
//POSSIBLE FIX: try to cut each key string at a "space" symbol
//and for each new string match the first 4 characters.
//so for "the rising shield hero" you can search
//the, rising, shield and hero.
//----------------------------------
//NOTE2: if there is more than 1 identical what to do?
//just return all identical matches.
//cannot have a list when doing a change (inc, remove).
//maybe require id when searching for an item you want to change (inc, remove)
//and to look up id you do a list search.
//then the vector match can ignore identicals, just return first best.
Dict vector_match(char key[S_SIZE], Vector vect)
{
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
                                return vect.data[i];
                        }
                }

                matches[i] = num_matches;
        }

        //Find largest in matches
        int cur_largest = matches[0];
        int best_match = 0;

        for(int i = 1; i < vect.size; i++)
        {
                if(matches[i] > cur_largest) {
                        best_match = i;
                        cur_largest = matches[i];
                }        
        }
        
        return vect.data[best_match];
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


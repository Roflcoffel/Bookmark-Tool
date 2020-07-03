#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "size.h"
#include "vector.h"
#include "util.h"
#include "action.h"

//executes a function based on id, when arg is a dirname, we enter strict mode
//strict mode only returns exact matches.
void action_execute(int id, char arg[S_SIZE], char format[S_SIZE], Vector *db)
{
        switch(id)
        {
                case 0:
                        action_list_all(*db);
                        break;
                case 1:
                        action_list_by_name(arg, format, *db);
                        break;
                case 2:
                        action_list_by_name(arg, format, *db);
                        break;
                case 3:
                        action_add(arg, db);
                        break;
                case 4:
                        action_remove(arg, db);
                        break;
                case 5:
                        action_inc(arg, db);
                        break;
                case 6:
                        action_edit(arg, db);
                        break;
                default:
                        break;
        }
}

//id: 0
void action_list_all(Vector db)
{
        for(int i = 0; i < db.size; i++)
        {
                printf("%d : %-20s -> %d\n", i, db.data[i].key, db.data[i].value);
        }
}

//id: 1
void action_list_by_name(char key[S_SIZE], char format[S_SIZE], Vector db)
{
        int index;
        Dict t = vector_find(key, db, &index);
        if(index != -1) {
                printf(format, index, t.key, t.value);
                return;
        }

        //No exact match was found try a partial match, with vector_match
        Vector vect = vector_match(key, db);

        //would be better to get the indexes from the vector_match, but this is simpler for now.
        int indexes[vect.size]; 

        for (size_t i = 0; i < vect.size; i++)
        {
                //Look up if &indexes[i] and &indexes+i are the same!
                vector_find(vect.data[i].key, db, &indexes[i]); 
        }
        
        for (int i = 0; i < vect.size; i++)
        {
                printf(format, indexes[i], vect.data[i].key, vect.data[i].value);
        }
       
}

//id: 3
void action_add(char key_value[S_SIZE], Vector *db)
{
        char ** name_split = str_split(key_value, ':');
        Dict pair = dict_new(name_split[0], atoi(name_split[1]));
        vector_add(pair, db);
        printf("Added:\n    -> %s\n    -> %d\n", pair.key, pair.value);

        free(name_split[0]); free(name_split[1]); free(name_split);
}

//id: 4
int action_remove(char id[S_SIZE], Vector *db)
{
        int index = atoi(id);
        if(valid_id(index, *db) == false)
        {
                printf("Id is not valid!\n");
                return 1;
        }

        printf("Removed:\n    -> %s\n", db->data[index].key);
        vector_remove(index, db);
       
        return 0;
}

//id: 5
int action_inc(char id[S_SIZE], Vector *db)
{
        int index = atoi(id);
        if(valid_id(index, *db) == false)
        {
                printf("Id is not valid!\n");
                return 1;
        }

        db->data[index].value++;
        printf("Increased:\n    -> %s\n    to %d\n", db->data[index].key, db->data[index].value);

        return 0;
}

//id: 6
int action_edit(char id_value[S_SIZE], Vector *db) 
{
        char ** split_value = str_split(id_value, ':');
        if(strcmp(split_value[0], id_value) == 0) return 1;

        int index = atoi(split_value[0]);
        int value = atoi(split_value[1]);

        free(split_value[0]); free(split_value[1]); free(split_value);
        
        if(valid_id(index, *db) == false)
        {
                printf("id is not valid\n");
                return 1;
        }

        db->data[index].value = value;
        printf("Changed:\n    -> %s\n    to %d\n", db->data[index].key, db->data[index].value);

        return 0;
}
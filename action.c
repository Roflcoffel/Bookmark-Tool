#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "size.h"
#include "util.h"
#include "vector.h"
#include "action.h"

//executes a function based on id, when arg is a dirname, we enter strict mode
//strict mode only returns exact matches.
void action_execute(int id, char name[S_SIZE], bool strict_mode, Vector *db)
{
        switch(id)
        {
                case 0:
                        action_list_all(*db);
                        break;
                case 1:
                        if(strict_mode) {
                                action_list_by_name_strict(name, *db);
                        } else {
                                action_list_by_name(name, *db);
                        }
                        break;
                case 2:
                        //For now I assume the last value is --value. (until more flags are added)
                        if(strict_mode) {
                                action_list_by_name_ret_val_strict(name, *db);
                        } else {
                                action_list_by_name_ret_val(name, *db);
                        }
                        break;
                case 3:
                        action_add(name, db);
                        break;
                case 4:
                        action_remove(name, db);
                        break;
                case 5:
                        action_inc(name, db);
                        break;
                default:
                        printf("Function was not found\n");
                        break;
        }
}

//id: 0
void action_list_all(Vector db)
{
        for(int i = 0; i < db.size; i++)
        {
                printf("%.10d : %.20s -> %d\n", i, db.data[i].key, db.data[i].value);
        }
}

//id: 1
void action_list_by_name(char name[S_SIZE], Vector db)
{
        Vector vect = vector_match(name, db);
        for (int i = 0; i < vect.size; i++)
        {
                printf("%.10d : %.20s -> %d\n", i, vect.data[i].key, vect.data[i].value);
        }
}

//id: 1 Strict
void action_list_by_name_strict(char name[S_SIZE], Vector db)
{
        int index;
        Dict t = vector_find(name, db, &index);
        printf("%.10d : %.20s -> %d\n", index, t.key, t.value);
}

//id: 2
void action_list_by_name_ret_val(char name[S_SIZE], Vector db)
{
        Vector vect = vector_match(name, db);
        for (int i = 0; i < vect.size; i++)
        {
                printf("%d\n", vect.data[i].value);
        }      
}

//id: 2 Strict
void action_list_by_name_ret_val_strict(char name[S_SIZE], Vector db)
{
        int index;
        Dict t = vector_find(name, db, &index);
        printf("%d\n", t.value);
}

//id: 3
void action_add(char name[S_SIZE], Vector *db)
{
        char ** name_split = str_split(name, ':');
        Dict pair = dict_new(name_split[0], atoi(name_split[1]));
        vector_add(pair, db);
        printf("Added:\n    -> %.20s\n    -> %d\n", pair.key, pair.value);
}

//id: 4
void action_remove(char id[S_SIZE], Vector *db)
{
        int index = atoi(id);
        if(valid_id(index, *db) == false)
        {
                printf("Id is not valid!\n");
                return 1;
        }
        
        vector_remove(index, db);
        printf("Removed:\n    -> %.20s\n", db->data[index].key);
}

//id: 5
void action_inc(char id[S_SIZE], Vector *db)
{
        int index = atoi(id);
        if(valid_id(index, *db) == false)
        {
                printf("Id is not valid!\n");
                return 1;
        }

        db->data[index].value++;
        printf("Increased:\n    -> %.20s\n    to %d\n", db->data[index].key, db->data[index].value);
}
#include <stdio.h>

#include "vector.h"
#include "action.h"

//executes a function based on id
void action_execute(int id, char key[255], Vector *db)
{
        switch(id)
        {
                case 0:
                        action_list_all(*db);
                        break;
                case 1:
                        action_list_by_name(key, *db);
                        break;
                case 2:
                        action_add(key, db);
                        break;
                case 3:
                        action_remove(key, db);
                        break;
                case 4:
                        action_inc(key, db);
                        break;
                default:
                        printf("Function was not found\n");
                        break;
        }
}

//id: 0
//Skip NULL objects
void action_list_all(Vector db)
{
        for(int i = 0; i < db.size; i++)
        {
                printf("%.20s -> %d\n", db.data[i].key, db.data[i].value);
        }
        
}

//id: 1
void action_list_by_name(char name[255], Vector db)
{
        Dict t = vector_find(name, db);
        printf("%.20s -> %d\n", t.key, t.value);
}

//id: 2
void action_add(char name[255], Vector *db)
{
        //Create a dict from the name;
        //it should contain a : as delimiter.
        //left side is the *name*
        //right side is the *value*
        //wow:1

        Dict pair = dict_new(name, 0); //Temp
        vector_add(pair, db);
        printf("Added:\n    -> %.20s\n    -> %d\n", pair.key, pair.value);
}

//id: 3
void action_remove(char name[255], Vector *db)
{
        vector_remove(name, db);
        printf("Removed:\n    -> %.20s\n", name);
}

//id: 4
void action_inc(char name[255], Vector *db)
{
        int index = vector_find_index(name, *db);
        db->data[index].value++;
        printf("Increased:\n    -> %.20s\n    to %d", name, db->data[index].value);
}
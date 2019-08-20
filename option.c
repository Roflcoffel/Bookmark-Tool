#include "vector.h"
#include "option.h"
//All commands / options

//Key defines action / name
//Value defines number of arguments
//Index of the item defines function id
void option_init(void)
{
        options = vector_new();
        //list
        vector_add(
                dict_new("list", type_new_i(0)),
                &options
        );
        //list test
        vector_add(
                dict_new("list", type_new_i(1)),
                &options
        );

        //add test:1
        vector_add(
                dict_new("add", type_new_i(1)),
                &options
        );

        //remove test
        vector_add(
                dict_new("remove", type_new_i(1)),
                &options
        );

        //inc test
         vector_add(
                dict_new("inc", type_new_i(1)),
                &options
        );
}
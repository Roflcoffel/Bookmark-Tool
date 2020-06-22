#include <stdbool.h>

#include "size.h"
#include "vector.h"
#include "command.h"

//Key defines action / name
//Value defines number of arguments
//Index of the item defines function id
void command_init(Vector * commands)
{
        vector_add( dict_new("list",   0), commands );
        vector_add( dict_new("list",   1), commands );
        vector_add( dict_new("list",   2), commands );
        vector_add( dict_new("add",    1), commands );
        vector_add( dict_new("remove", 1), commands );
        vector_add( dict_new("inc",    1), commands );
        vector_add( dict_new("edit",   1), commands );
}
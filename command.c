#include "vector.h"
#include "command.h"

//Key defines action / name
//Value defines number of arguments
//Index of the item defines function id
void command_init(void)
{
        commands = vector_new();
    
        vector_add( dict_new("list",   0), &commands );
        vector_add( dict_new("list",   1), &commands );
        vector_add( dict_new("add",    1), &commands );
        vector_add( dict_new("remove", 1), &commands );
        vector_add( dict_new("inc",    1), &commands );
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"
#include "size.h"

#include "vector.h"
#include "command.h"
#include "action.h"
#include "util.h"
#include "file.h"
#include "color.h"

#define USAGE "lots of help text\n"
#define FULLPATH PATH FILENAME

void set_default(Vector *db);

//TODO for 1.0:
// define array string sizes in logical place (should exist in size.h)
// makes sure that db always have some data, some function may be confused otherwise (vector_match)
// print current version and help if no COMMAND is provided
// in README.md example show what the expected output is for each command.
// padding spaces for action outputs

//## FLAGS ##
//--dirkey  - Use the current dir as the key
//--value   - only display the value of the pair
//--key     - only display the key of the pair

//## Memory Leaks ##
// use valgrind on (vector / util / file).

// 1.1: 
// instead of a next command:
// Add a next bash script, with this vlc $(sel.sh $(( $(bookmark list serie_id --value)+1 )))
// and at the end, bookmark inc serie_id

int main(int argc, const char* argv[]) 
{
        //Initiate all basic commands
        command_init();
        
        Vector db = vector_new();
        Vector default_db = vector_new();
        
        set_default(&default_db);
        
        //Read from file or create
        file_init(FULLPATH, &db, default_db);
        
        if(argc <= 1) {
                printf(USAGE);
                return 0;
        }

        //User option (list, add, remove, inc)
        char opt[S_SIZE];
        strcpy(opt, argv[1]);

        print_color(BLUE, "option: ");
        printf("%s\n", opt);

        //User argument (key name);
        char arg[S_SIZE];

        //strcmp return 1 or -1 when the string do not match
        if(argc >= 3 && strcmp("NULL", argv[2]) != 0) {
              strcpy(arg, argv[2]);
              print_color(BLUE, "argument: ");
              printf("%s\n", arg);
        }
        
        int arg_count = argc - 2; //Discard filename and option
        print_color(BLUE, "argument count: ");
        printf("%d\n",arg_count);

        bool action_done = false;

        //for(int i = 0; i < commands.size; i++)
        //{
        //        if((strcmp(commands.data[i].key,opt) == 0) && (commands.data[i].value.INT == arg_count)) {
        //                action_execute(i, arg, &db);
        //                action_done = true;
        //                break;
        //        }
        //}

        if(!action_done)
        {
                printf("Invalid commands and argument!\n");
                return 0;
        }

        //Write all changes in the db vector to a file

        vector_destroy(&db);
        vector_destroy(&default_db);
        vector_destroy(&commands);

        return 0;
}

void set_default(Vector *db)
{
        vector_add(dict_new("default",0), db);
}
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

#define VERSION "Bookmark - 0.9\n"
#define USAGE "Usage: bookmark [COMMAND] key[:value]\n\n" \
              "COMMANDS:\n" \
              "    list   - [name]     ; list all or a specified pair, also displays id\n" \
              "    add    - name:value ; creates a new name:value pair\n" \
              "    remove - id         ; remove the pair with the provided id\n" \
              "    inc    - id         ; increases the value of the pair with the povided id\n\n" \
              "FLAGS:\n" \
              "    list --dir_as_name  ; instead of providing a name use the current dir as the name\n" \
              "    list --value        ; returns only the value of the pair\n\n" \
              "NOTES:\n" \
              "    [] means optional\n" \
              "    no command = list\n" \
              "    flags are only useable with list\n"

#define FULLPATH PATH FILENAME

void set_default(Vector *db);

//TODO for 1.0:
// error checking for str_split, either pass in bool for status, or return failed in char*
// valid_id maybe should be a function inside of vector.c instead of util.c
// Test vector_find, added argument
// in README.md example show what the expected output is for each command.
// padding spaces for action outputs
// implement the flags

//## Memory Leaks ##
// use valgrind on (vector / util / file).

// 1.1: 
// instead of a next command:
// Add a next bash script, with this vlc $(sel.sh $(( $(bookmark list serie_id --value)+1 )))
// and at the end, bookmark inc serie_id

// if we save the index of the null object, we could simply skip it when writing the file
// but we need to pass around more arguments.
// action_remove could return the index with an argument?

int main(int argc, const char* argv[]) 
{
        //Initiate all basic commands
        command_init();
        
        Vector db = vector_new();
        Vector default_db = vector_new();
        
        set_default(&default_db);
        
        //Read from file or create
        file_init(FULLPATH, &db, default_db);

        printf("FULLPATH: %s", FULLPATH);
        
        if(argc <= 1) {
                printf(USAGE);
                return 0;
        }

        //User option (list, add, remove, inc)
        char cmd[S_SIZE];
        strcpy(cmd, argv[1]);

        print_color(BLUE, "Command: ");
        printf("%s\n", cmd);

        //User data input string
        char arg[S_SIZE];

        //strcmp return 1 or -1 when the strings do not match
        if(argc >= 3 && strcmp("NULL", argv[2]) != 0) {
              strcpy(arg, argv[2]);
              print_color(BLUE, "argument: ");
              printf("%s\n", arg);
        }

        //bookmark list --dir_as_name
        //here check if arg is --dir_as_name, and if it is call a function which gets the dir, and use that as arg
        bool arg_is_dirname = false;

        int arg_count = argc - 2; //Discard filename and option
        print_color(BLUE, "argument count: ");
        printf("%d\n",arg_count);

        bool action_done = false;

        //for(int i = 0; i < commands.size; i++)
        //{
        //        if((strcmp(commands.data[i].key,cmd) == 0) && (commands.data[i].value.INT == arg_count)) {
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
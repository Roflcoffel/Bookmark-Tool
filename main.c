#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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
// RUN TESTS
// Test the main program
// implement dir_as_name flag
// in README.md example show what the expected output is for each command.
// padding spaces for action outputs

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

        printf("FULLPATH: %s", FULLPATH);
        
        if(argc <= 1) {
                printf(VERSION USAGE);
                return 0;
        }

        //User option (list, add, remove, inc)
        char cmd[S_SIZE];
        int cmd_id;
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

        bool arg_is_dirname = false;
        char cwd[S_SIZE];

        //Check for the dir flag, and replace arg with cwd
        if(strcmp("--dir_as_name", arg) == 0) {
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        arg_is_dirname = true;
                        strcpy(arg, cwd);
                } 
        }

        printf("ARG: %s", arg);

        int arg_count = argc - 2; //Discard filename and option
        print_color(BLUE, "argument count: ");

        bool action_done = false;

        /*
        for(int i = 0; i < commands.size; i++)
        {
                if((strcmp(commands.data[i].key,cmd) == 0) && (commands.data[i].value == arg_count)) {
                       action_execute(i, arg, arg_is_dirname, &db);
                       cmd_id = i;
                       action_done = true;
                       break;
                }
        }
        */

        if(!action_done)
        {
                printf("Invalid commands and argument!\n");
                return 0;
        }

        //check if we need to update the file!
        //list       ids: 0, 1, 2
        //add,rm,inc ids: 3, 4, 5
        //if(cmd_id >= 3) file_write(FULLPATH, db);

        vector_destroy(&db);
        vector_destroy(&default_db);
        vector_destroy(&commands);

        return 0;
}

void set_default(Vector *db)
{
        vector_add(dict_new("default",0), db);
}
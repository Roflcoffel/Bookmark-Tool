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
// Real world testing
// Create a simple install script.
// in README.md example show what the expected output is for each command.

//## Memory Leaks ##
// use valgrind on (vector / util / file).

// 1.1: 
// edit command, to change to value of a pair. (useful when making a mistake)
// instead of a next command:
// PlayNext.sh [serie_id]
// Add a next bash script, with this vlc $(sel.sh $(( $(bookmark list serie_id --value)+1 )))
// and at the end, bookmark inc serie_id

int main(int argc, const char* argv[]) 
{
        //Initiate all basic commands
        Vector commands = vector_new();
        command_init(&commands);
        
        Vector db = vector_new();
        Vector default_db = vector_new();
        
        set_default(&default_db);
        
        //Read from file or create
        file_init(FULLPATH, &db, default_db);
        
        if(argc <= 1) {
                printf(VERSION USAGE);
                return 0;
        }

        //User option (list, add, remove, inc)
        char cmd[S_SIZE];
        int cmd_id;
        strcpy(cmd, argv[1]);

        print_color(CYAN, "Command: ");
        printf("%s\n", cmd);

        //User data input string
        char arg[S_SIZE];

        //strcmp return 1 or -1 when the strings do not match
        if(argc >= 3 && strcmp("NULL", argv[2]) != 0) {
              strcpy(arg, argv[2]);
              print_color(CYAN, "argument: ");
              printf("%s\n", arg);
        }

        bool arg_is_dirname = false;
        char cwd[S_SIZE];

        //Check for the dir flag, and replace arg with cwd
        if(strcmp("--dir_as_name", arg) == 0) {
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        arg_is_dirname = true;
                        size_t size;
                        char ** cwd_split = multi_str_split(cwd, '/', &size);

                        strcpy(arg, cwd_split[size-1]);
                        char_replace(arg, '_', ' ');

                        free_array(cwd_split, size);
                } 
        }

        printf("ARG: %s\n", arg);

        int arg_count = argc - 2; //Discard filename and option
        print_color(CYAN, "argument count: ");
        printf("%d\n", arg_count);

        bool action_done = false;

        for(int i = 0; i < commands.size; i++)
        {
                if((strcmp(commands.data[i].key,cmd) == 0) && (commands.data[i].value == arg_count)) {
                       action_execute(i, arg, arg_is_dirname, &db);
                       cmd_id = i;
                       action_done = true;
                       break;
                }
        }

        if(!action_done)
        {
                print_color(RED, "Invalid commands and argument!\n");
                printf(USAGE);
                return 0;
        }

        //check if we need to update the file!
        //list       ids: 0, 1, 2
        //add,rm,inc ids: 3, 4, 5
        if(cmd_id >= 3) file_write(FULLPATH, db);

        vector_destroy(&db);
        vector_destroy(&default_db);
        vector_destroy(&commands);

        return 0;
}

void set_default(Vector *db)
{
        vector_add(dict_new("default",0), db);
}
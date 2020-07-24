#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "test_config.h" //CHANGE THIS TO config.h, before make install
#include "size.h"

#include "vector.h"
#include "command.h"
#include "action.h"
#include "util.h"
#include "file.h"
#include "color.h"

#define VERSION "Bookmark - 1.0\n"
#define USAGE "Usage: bookmark [COMMAND] key[:value]\n\n" \
              "COMMANDS:\n" \
              "    list   - [name]      ; list all or a specified pair, also displays id\n" \
              "    list   - name format ; specify a C-Style format, to modify the ouput\n" \
              "    add    - name:value  ; creates a new name:value pair\n" \
              "    remove - id          ; remove the pair with the provided id\n" \
              "    inc    - id          ; increases the value of the pair with the povided id\n" \
              "    edit   - id:value    ; changes the value of the pair with the provided id\n" \
              "    undo   -             : reverses the effect of the previous command\n\n" \
              "FLAGS:\n" \
              "    list --dir_as_name   ; instead of providing a name use the current dir as the name\n" \
              "NOTES:\n" \
              "    [] means optional\n" \
              "    flags are only useable with list\n"

#define FULLPATH PATH FILENAME
#define BACKUP_PATH PATH BACKUP

//TODO 1.1:
// Real world testing
// Garbage seems to be gone, check in Real world testing!

//## Memory Leaks ##
// use valgrind on (vector / util / file).c

//## Tweaks ##
//when looping through a string, instead of using strlen and for loop,
//you can try using a for loop, and look for the null character


int main(int argc, const char* argv[]) 
{       
        if(argc <= 1) {
                printf(VERSION USAGE);
                return 0;
        }

        char arg[S_SIZE]; //Arguments to the command
        char cmd[S_SIZE]; //The command to run
        char cwd[S_SIZE]; //Current Working Directory

        //Format Argument, Default value
        char format[S_SIZE] = "%d : %-*s -> %d\n"; 
        
        //The id for the command executed
        int cmd_id = 0;

        //Initiate all basic commands
        Vector commands = vector_new();
        command_init(&commands);
        
        Vector db         = vector_new();
        Vector backup_db  = vector_new();
        
        //Read from file or create
        file_init(FULLPATH, &db);
        file_init(BACKUP_PATH, &backup_db);

        //Here the garbage gets added to the multi_str_split, still don't know why,
        //it have to be something in file_init.
        //CURRENT HACK SOLUTION
        //running the command once seems to "clean" the ouput, so this is the solution for now

        //So if the string is 22 and there are 3 items, we still have garbage on the second multi_str_split
        //if I add an item so we have 4, then both works.
        //May be a problem when there is exactly three, (or maybe less) it causes the problem but only
        //to the next multi_str_split call, strange...
        //size_t garb_size = 0;
        //char ** garb = multi_str_split("/clean/random/garbage/four", '/', &garb_size);
        //printf("%s\n", garb[0]);
        //free_array(garb, garb_size); free(garb);

        //Current Command
        strcpy(cmd, argv[1]);

        //Check if db is empty, 
        //if we have zero data in the file and we are not doing a add command
        if(db.size == 0 && strcmp("add", cmd) != 0)
        {
                printf("There is no data in db.csv, add data with the add command!\n");
                return 0;
        }

        //Check if the third argument exists.
        if(argc >= 3 && strcmp("NULL", argv[2]) != 0) 
                strcpy(arg, argv[2]);

        //Check for the last argument.
        if(argc >= 4 && strcmp("NULL", argv[3]) != 0)
                strcpy(format, argv[3]);

        //Check for the dir flag, and replace arg with cwd
        if(strcmp("--dir_as_name", arg) == 0) {
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        size_t size = 0;

                        char ** cwd_split = multi_str_split(cwd, '/', &size);

                        strcpy(arg, cwd_split[size-1]);
                        char_replace(arg, '_', ' ');

                        free_array(cwd_split, size); free(cwd_split);
                } 
        }

        int arg_count = argc - 2; //Discard filename and option
        bool action_done = false;

        for(int i = 0; i < commands.size; i++)
        {
                if((strcmp(commands.data[i].key,cmd) == 0) && (commands.data[i].value == arg_count)) {
                       action_execute(i, arg, format, &db, backup_db);
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
        //list                 ids: 0, 1, 2,
        //add,rm,inc,edit,undo ids: 3, 4, 5, 6, 7
        if(cmd_id >= 3) 
        {
                file_copy(FULLPATH, BACKUP_PATH); //Copy old file before updating
                file_write(FULLPATH, db);
        }

        vector_destroy(&db);
        vector_destroy(&commands);
        
        return 0;
}
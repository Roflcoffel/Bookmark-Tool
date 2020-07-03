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
              "    list   - [name]      ; list all or a specified pair, also displays id\n" \
              "    list   - name format ; specify a C-Style format, to modify the ouput\n" \
              "    add    - name:value  ; creates a new name:value pair\n" \
              "    remove - id          ; remove the pair with the provided id\n" \
              "    inc    - id          ; increases the value of the pair with the povided id\n\n" \
              "    edit   - id:value    ; chances the value of the pair with the provided id\n\n" \
              "FLAGS:\n" \
              "    list --dir_as_name   ; instead of providing a name use the current dir as the name\n" \
              "NOTES:\n" \
              "    [] means optional\n" \
              "    no command = list\n" \
              "    flags are only useable with list\n"

#define FULLPATH PATH FILENAME

void set_default(Vector *db);

//REMEMBER TO CHANGE CONFIG, BEFORE EXECUTING INSTALL!

//TODO for 1.0:
// Test if str_split and multi_str_split still works, added free() to the substring calls.
// Real world testing
// Configuration, should look up how to do this porperly with make
// Just need to learn what you can do with make

//## Memory Leaks ##
// use valgrind on (vector / util / file).

//for PlayNext.sh
//Maybe a plugin for vlc, can increment the bookmark instead of PlayNext
//this is to make sure that every time PlayNext is called the episode i assumed
//to be watched, a small plugin can look at the time and increment bookmark when
//we are half way through an episode.

//to increment we need the id, so may need to add a get id command
//it would look like this: 
//bookmark get_id name
//bookmark get_id --dir_as_value
//--dir_as_value just resolves itself to a directory name, meaning
//it can be treated as get_id name
//the question now is name in this context should this be a strict match or non strict.
//because match can return more than one value, this should be a strict match.

//instead of a command, get_id can just be a flag, only problem is that I am not handling
//flags in a good way

//think of a good way to handle flags, the id flag would only be just with the list ofcourse
//and should only really change the output.

//bookmark list name --id           ; would return all ids that matches name
//bookmark list --dir_as_value --id ; would only return a single value

//if this is the last flag, I guess checking it in action can be okej, right now we always
//assume the flag is --value beacuse there is only flag

//instead of handling flags, the last command can always be interpretted as a string format
//so we can just pass in how we want to format the output, this feels like the most elegant way.
//is there a way to format three variables, so that only one of the is displayed
//meaning can we turn: printf("%d, %s, %d", id, key, value); to a format that only displays
//the id, or the value
//%.0s prints the argument with 0 width, so with that we can print positional arguments
//the format to provide is a little weird but I think it is an okay solution.
//to get only the value: "%.0s%.0s%d"
//to get only the id   : "%d%.0s%.0s"

//this also removes the current value flag, and hopfully simplfies the code.
//it will also be possible to format in ways that I cannot think of, which may accedentily solve
//some other problem, or command I want to add.

//instead of a strict and non strict function, we can always first do a strict.
//and then if no value was returned we try a vector_match instead.

//this would remove two strict function, and some ifs and a bool.
//and only make the function a little longer.

//## Ideas / Optimisations
//the returns in action can be used for error handling
// maybe add a file for error handling hmmmmm...

//when looping through a string, instead of using strlen and for loop,
//you can try using a while, and look for the null character

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
        char format[S_SIZE] = "%d : %-20s -> %d\n"; 
        
        //The id for the command executed
        int cmd_id = 0;

        //Initiate all basic commands
        Vector commands = vector_new();
        command_init(&commands);
        
        Vector db         = vector_new();
        Vector default_db = vector_new();
        set_default(&default_db);
        
        //Read from file or create
        file_init(FULLPATH, &db, default_db);

        //Here the garbage gets added to the multi_str_split, still don't know why,
        //it have to be something in file_init.
        //CURRENT HACK SOLUTION
        //running the command once seems to "clean" the ouput, so this is the solution for now

        //So if the string is 22 and there are 3 items, we still have garbage on the second multi_str_split
        //if I add an item so we have 4, then both works.
        //May be a problem when there is exactly three, (or maybe less) it causes the problem but only
        //to the next multi_str_split call, strange...
        size_t garb_size = 0;
        char ** garb = multi_str_split("/clean/random/garbage/four", '/', &garb_size);
        //printf("%s\n", garb[0]);
        free_array(garb, garb_size); free(garb);

        //Current Command
        strcpy(cmd, argv[1]);

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
                       action_execute(i, arg, format, &db);
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
        //list            ids: 0, 1, 2
        //add,rm,inc,edit ids: 3, 4, 5, 6
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
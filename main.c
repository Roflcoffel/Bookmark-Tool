#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.h"
#include "command.h"
#include "action.h"
//#include "util.c"
//#include "file.c"
#include "color.h"

#define USAGE "lots of help text\n"

void setTempData(Vector *db);

//TODO for 1.0:
//## Memory Leaks ##
// use valgrind on util to see if there are any memory leaks

//## Fixes ##
// define array string sizes in logical place
// makes sure that db always have some data, some function may be confused otherwise (vector_match)
// id will be represented as the index, or may save it in the Dict type.

//## New Stuff ##
// flag for list [name], which will display only the episode number (so it can be piped)
// print current version and help if no COMMAND is provided
// in README.md example show what the expected output is for each command.
// padding spaces for action outputs
// best match function

//## Tests ##
// test vector.c, vector_match got changed.
// test file.c
// in the unit test, always print current value and the expected, this can be a verbose setting.
// on an assert it would be helpful to know both the current value and the expected value.

// 1.1: 
// lets add a "next" command
// which all "next" does is print the next episode number in a series. (cur+1)
// and with a simple bash function call vlc $(sel.sh $(bookmark next $serie)) 
// would play the next episode.
// sel.sh can be included in the project as an example usage of next.
// the next command would also serve as a quick reminder
// the only problem is that next would be more robust with ids (vector index == ids?)
// this ofc crates a small annoyance where you have to look up the id then you can do execute next

// Recent Idea:
// instead of searching for a series, it would be pretty easy to assume a serie.
// so to assume a serie all we need to look at is what the current directory is.
// and use that as the search.
// most useful for commands that change the data in db.

// Vector Remove:
// Not doing a realloc is fine because of the lifetime of the program, the intended use
// makes it so that after a command is processed we write to the file and the program terminates.
// so we will never have more than one "fake" null object in the array, and when we write a null
// to the file we simply ignore it, just need to make sure that rewrite the whole file when we
// do a change.
int main(int argc, const char* argv[]) 
{
        //Initiate all basic commands
        command_init();
        //Read from file or create
        Vector db = vector_new();
        //file_init("db.csv", &db);
        setTempData(&db);

        if(argc <= 1) {
                printf(USAGE);
                return 0;
        }

        //User option (list, add, remove, inc)
        char opt[255];
        strcpy(opt, argv[1]);

        print_color(BLUE, "option: ");
        printf("%s\n", opt);

        //User argument (key name);
        char arg[255];

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

        //Testing vector_match
        Vector test = vector_match(arg, db);
        printf("%s\n",test.data[0].key);

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
        vector_destroy(&commands);

        return 0;
}

void setTempData(Vector *db)
{
        vector_add( dict_new("Aishiteruze Baby", 25), db);
        vector_add( dict_new("The Rising of The Shield Hero", 15), db);
        vector_add( dict_new("Black Clover", 79), db);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vector.c"
#include "option.c"
#include "action.c"
//#include "util.c"
//#include "file.c"
#include "color.c"

#define USAGE "lots of help text\n"

void setTempData(Vector *db);

//TODO for 1.0:
// 1. UNIT TEST / a sperate program that does just testing.
// 1.1 -> best match, 
// 1.2 -> util.substring, 
// 1.3 -> util.split
// test file.c
// define array string sizes in logical place
// create a make file
// makes sure that db always have some data, some function may be confused otherwise (vector_match)
// set a short name, so its easier to search. (ex. The Rising Sheild Hero = Shield) or just have an id.
// flag for list [name], which will display only the episode number (so it can be piped)
// change option to command maybe?
// print current version and help if no COMMAND is provided
// in README.md example show what the expected output is for each command.
// padding spaces for action outputs
// include h files instead of c (think its more proper?)
// seems to be proper to compile each file in its own vaccum, so each file .c that requires stdio should alsways include it.

// 1.1: 
// lets add a "next" command
// which all "next" does is print the next episode number in a series. (cur+1)
// and with a simple bash function call vlc $(sel.sh $(bookmark next $serie)) 
// would play the next episode.
// sel.sh can be included in the project as an example usage of next.
// the next command would also serve as a quick reminder
// the only problem is that next would be more robust with ids (vector index == ids?)
// this ofc crates a small annoyance where you have to look up the id then you can do execute next
int main(int argc, const char* argv[]) 
{
        //Initiate all basic commands
        option_init();
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
        Dict test = vector_match(arg, db);
        printf("%s\n",test.key);

        //for(int i = 0; i < options.size; i++)
        //{
        //        if((strcmp(options.data[i].key,opt) == 0) && (options.data[i].value.INT == arg_count)) {
        //                action_execute(i, arg, &db);
        //                action_done = true;
        //                break;
        //        }
        //}

        if(!action_done)
        {
                printf("Invalid options and argument!\n");
                return 0;
        }

        //Write all changes in the db vector to a file

        vector_destroy(&db);
        vector_destroy(&options);

        return 0;
}

void setTempData(Vector *db)
{
        vector_add(
                dict_new("Aishiteruze Baby", type_new_i(25)),
                db
        );
        vector_add(
                dict_new("The Rising of The Shield Hero", type_new_i(15)),
                db
        );
        vector_add(
                dict_new("Black Clover",type_new_i(79)),
                db
        );
}
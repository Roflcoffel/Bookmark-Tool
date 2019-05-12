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

//TODO:
// test util.substring and util.split
// padding spaces for action outputs
// test file.c
// define array string sizes in logical place
// create a make file
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

        char opt[255];
        strcpy(opt, argv[1]);

        print_color(BLUE, "option: ");
        printf("%s\n", opt);

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
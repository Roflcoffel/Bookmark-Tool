//file.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "vector.h"
#include "util.h"
#include "file.h"

//Reads and stores it in db if the file exists
//Otherwise create a empty file.
void file_init(char filename[], Vector *db)
{
        FILE *fp = fopen(filename, "r");
        if(fp) {
                file_to_vector(fp, db);
        }
        else {
                FILE *empty_file = fopen(filename, "w");
                fclose(empty_file);
        }
}

//Writes a vector to a file if it DOES NOT EXIST, also creats the file.
void file_simple(char filename[], Vector db)
{
        FILE *fp = fopen(filename, "r"); //r : read a file it must exist otherwise it returns NULL.
        fp ? fclose(fp) : file_write(filename, db);
}

//Always creates a file and writes a vector to it, also replaces any existing file.
void file_write(char filename[], Vector db)
{
        FILE *fp = fopen(filename, "w"); //w : always creates a file, replaces any existing.
        fp ? vector_to_file(fp, db) : printf("Insufficent Permissions\n"); //or file not found
}

//Reads a file and save it to a vector.
void file_read(char filename[], Vector *db)
{
        FILE *fp = fopen(filename, "r");
        fp ? file_to_vector(fp, db) : printf("Insufficent Permissions\n"); //or file not found
}

//Copies a soruce file to a target file.
void file_copy(char source[], char target[])
{
        FILE *fp_source = fopen(source, "r");
        if(fp_source == NULL) exit(EXIT_FAILURE); //file not found abort.

        FILE *fp_target = fopen(target, "w");
        if(fp_target == NULL) exit(EXIT_FAILURE); ////file not found abort.
        //fp_target should not be able to be null, because "w" creates a file if it does not exist.
        
        char c;
        while( ( c = fgetc(fp_source) ) != EOF ) fputc(c, fp_target);

        fclose(fp_source); fclose(fp_target);
}

//READS a file and saves it to a vector
void file_to_vector(FILE *file, Vector *db)
{
        char lines[LINESIZE];

        while (fgets(lines, sizeof(lines), file)) {
                size_t size = 0;
                char ** s = multi_str_split(lines, ',', &size);
                vector_add(dict_new(s[0], atoi(s[1])), db);
                free_array(s, size); free(s);
        }
        fclose(file);
}

//WRITES a vector to a file
void vector_to_file(FILE *file, Vector db)
{
        for (int i = 0; i < db.size; i++)
        {
                if(strcmp("NULL", db.data[i].key) != 0)
                        fprintf(file, "%s,%d\n", db.data[i].key, db.data[i].value);
        }
        fclose(file);
}
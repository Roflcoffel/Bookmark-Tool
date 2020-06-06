//file.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "size.h"
#include "vector.h"
#include "util.h"
#include "file.h"

char lines[LINESIZE];

//Reads and stores it in db if the file exists, 
//otherwise writes a file with content of deafult_db
void file_init(char filename[S_FILENAME], Vector *db, Vector default_db)
{
        FILE *fp = fopen(filename, "r");
        if(fp) {
                file_to_vector(fp, db);
        }
        else {
                file_write(filename, default_db);
                vector_destroy(db);
                db = &default_db;   //db should now point to default_db
        }
}

//opens a file, and saves the content to a vector
void file_read(char filename[S_FILENAME], Vector *db)
{
        FILE *fp = fopen(filename, "r");
        fp ? file_to_vector(fp, db) : printf("File not found\n"); //Or Insufficent Permissions
}

//opens a file, and writes a vector to it
void file_write(char filename[S_FILENAME], Vector db)
{
        FILE *fp = fopen(filename, "w");
        fp ? vector_to_file(fp, db) : printf("File not found\n"); //or Insufficent Permissions
}

//READS a file and save it to a vector
void file_to_vector(FILE *file, Vector *db)
{
        while (fgets(lines, sizeof(lines), file)) {
                char ** s = str_split(lines, ',');
                vector_add(dict_new(s[0], atoi(s[1])), db);
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
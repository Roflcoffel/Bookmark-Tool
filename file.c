//file.c
#include "file.h"
#define MAXCHAR 1000

char lines[MAXCHAR];

void file_init(char filename[255], Vector *db)
{
        FILE *fp = fopen(filename, "a+");
        file_to_vector(fp, db);
        fclose(fp);
}

void file_write(FILE *file, char line[255])
{
        fprintf(file, line);
}

void file_to_vector(FILE *file, Vector *db)
{
        while (fgets(lines, MAXCHAR, file) != NULL) {
                char s[2][MAXCHAR] = str_split(lines, ',');
                vector_add(
                        dict_new(s[0], type_new_i(atoi(s[1]))), 
                        db
                );
        }
}
//file.c
#include <stdio.h>
#include "file.h"
#include "vector.h"

char lines[LINESIZE];

void file_init(char filename[S_FILENAME], Vector *db)
{
        FILE *fp = fopen(filename, "a+");
        file_to_vector(&fp, &db);
}

void file_write(FILE *file, char line[LINESIZE])
{
        fprintf(file, line);
        fclose(file);
}

void file_to_vector(FILE *file, Vector *db)
{
        while (fgets(lines, sizeof(lines), file)) {
                char s[2][LINESIZE] = str_split(lines, ',');
                vector_add(dict_new(s[0], atoi(s[1])), &db);
        }
        fclose(file);
}
#ifndef FILE_H_
#define FILE_H_

#define LINESIZE 500

void file_to_vector(FILE *file, Vector *db);
void vector_to_file(FILE *file, Vector db);
void file_write(char filename[], Vector db);
void file_read(char filename[], Vector *db);
void file_init(char filename[], Vector *db);
void file_simple(char filename[], Vector db);
void file_copy(char source[], char target[]);

#endif
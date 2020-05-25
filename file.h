#ifndef FILE_H_
#define FILE_H_

#define LINESIZE 1000
#define S_FILENAME 255

void file_to_vector(FILE *file, Vector *db);
void file_write(FILE *file, char line[255]);
void file_init(char filename[255], Vector *db);

#endif
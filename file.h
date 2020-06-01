#ifndef FILE_H_
#define FILE_H_

void file_to_vector(FILE *file, Vector *db);
void file_read(char filename[S_FILENAME], Vector *db);
void vector_to_file(FILE *file, Vector db);
void file_write(char filename[S_FILENAME], Vector db);
void file_init(char filename[S_FILENAME], Vector *db, Vector default_db);

#endif
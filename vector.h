#ifndef VECTOR_H_
#define VECTOR_H_

#define INITAL_VECTOR_SIZE 2

typedef struct Dict
{
        char key[S_SIZE];
        int value;
} Dict;

typedef struct Vector
{
        Dict *data;     //Data in the array
        int size;       //The size of the array
        int capacity;   //The maximum capacity
} Vector;

Dict dict_new(char key[S_SIZE], int value);

Vector vector_new(void);
void vector_add(Dict dict, Vector *vect);
Vector vector_match(char key[S_SIZE], Vector vect);
Dict vector_find(char key[S_SIZE], Vector vect, int *index);
Dict vector_find_by_index(int index, Vector vect);
int vector_find_index(char key[S_SIZE], Vector vect);
void vector_remove(int index, Vector *vect);
void vector_destroy(Vector *vect);
void vector_inc(int index, Vector *vect);
bool valid_id(int index, Vector db);

#endif
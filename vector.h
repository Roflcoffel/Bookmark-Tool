#ifndef VECTOR_H_
#define VECTOR_H_

#define S_SIZE 255
#define DICT_SIZE 255
#define INITAL_VECTOR_SIZE 2

typedef struct Dict
{
        char key[DICT_SIZE];
        int value;
} Dict;

typedef struct Vector
{
        Dict *data;     //Data in the array
        int size;       //The size of the array
        int capacity;   //The maximum capacity
} Vector;

Dict dict_new(char key[255], int value);

Vector vector_new(void);
void vector_add(Dict dict, Vector *vect);
Dict vector_match(char key[255], Vector vect);
Dict vector_find(char key[255], Vector vect);
Dict vector_find_by_index(int index, Vector vect);
int vector_find_index(char key[255], Vector vect);
void vector_remove(char key[255], Vector *vect);
void vector_destroy(Vector *vect);
void vector_inc(int index, Vector *vect);

#endif
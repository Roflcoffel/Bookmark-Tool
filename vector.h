#ifndef VECTOR_H_
#define VECTOR_H_

#define INITAL_VECTOR_SIZE 2
#define MAX_KEY 255

typedef struct Dict
{
        char key[MAX_KEY];
        int value;
} Dict;

typedef struct Vector
{
        Dict *data;     //Data in the array
        int size;       //The size of the array
        int capacity;   //The maximum capacity
} Vector;

Dict dict_new(char key[], int value);

Vector vector_new(void);
void vector_add(Dict dict, Vector *vect);
Vector vector_match(char key[], Vector vect);
Dict vector_find(char key[], Vector vect, int *index);
int vector_find_index(char key[], Vector vect);
int vector_longest_key(Vector vect);
void vector_remove(int index, Vector *vect);
void vector_destroy(Vector *vect);
void vector_inc(int index, Vector *vect);
bool valid_id(int index, Vector db);

#endif
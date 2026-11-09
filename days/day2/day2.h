#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int* factor(int number_of_letters, int *result_size);
int check_symmetry(char *src, int *divisors, int divisor_length);
int check_repetition(char *src);

typedef struct
{
    char *start;
    char *end;
}range;

typedef struct 
{
    int size;
    int capacity;
    range **data;
}vector;

void vector_add(vector *v, range *r){
    if(v->size >= v->capacity){
        v->capacity *= 2;
        range **tmp = realloc(v->data, v->capacity * sizeof(*v->data));
        if (!tmp)
        {
            printf("realloc failed! returning..");
            v->capacity = v->capacity/2;
            return;
        }
        v->data = tmp;
    }
    v->data[v->size] = r;
    v->size = v->size +1;
    return;
}

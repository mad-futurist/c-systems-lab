#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "../libc/my_string.h"

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

Vector *init_vector(size_t capacity, size_t element_size);
int vector_push(const void *elem, Vector *vector);

int main(){


}

Vector *init_vector(size_t capacity, size_t element_size)
{
    if (capacity == 0 || element_size == 0) {
        return NULL;
    }

    Vector *vector = malloc(sizeof(Vector));

    if (vector == NULL) {
        return NULL;
    }

    vector->data = malloc(capacity * element_size);

    if (vector->data == NULL) {
        free(vector);
        return NULL;
    }

    vector->size = 0;
    vector->capacity = capacity;
    vector->element_size = element_size;

    return vector;
}

int vector_push(void *elem, Vector *vector){
    if(vector->size >= vector->capacity){
        return 1;
    }

    unsigned char *data = (unsigned char *)vector->data;

    void *dest = data + vector->size * vector->element_size;

    my_memcpy(dest,elem,vector->element_size);

    vector->size++;

    return 0;
}
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    void *data;
    size_t size;
    size_t capacity;
    size_t element_size;
} Vector;

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
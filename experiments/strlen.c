#include <stdio.h>
#include <stddef.h>

size_t my_strlen(const char *arr);

size_t my_strlen(const char *arr)
{
    const char *arr_base = arr;

    while (*arr != '\0') {
        arr++;
    }

    return (size_t)(arr - arr_base);
}

int main(void)
{
    char arr[] = {'a', 'b', 'c', '\0'};

    printf("%zu\n", my_strlen(arr));

    return 0;
}
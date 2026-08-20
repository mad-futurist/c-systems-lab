#include <stdio.h>
#include <stddef.h>



size_t my_strlen(const char *arr)
{
    const char *arr_base = arr;

    while (*arr != '\0') {
        arr++;
    }

    return (size_t)(arr - arr_base);
}

char *my_strcpy(char *dest, int dest_capacity, const char *src)
{
    char *start = dest;

    int needed = my_strlen(src) + 1;

    if(needed > dest_capacity){
        return NULL;
    }

    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return start;
}

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 < *str2) {
            return -1;
        }

        if (*str1 > *str2) {
            return 1;
        }

        str1++;
        str2++;
    }

    if (*str1 == '\0' && *str2 == '\0') {
        return 0;
    }

    if (*str1 == '\0') {
        return -1;
    }

    return 1;
}

void *my_memset(void *buffer, size_t size, unsigned char value)
{
    unsigned char *bytes = (unsigned char *)buffer;

    for (size_t i = 0; i < size; i++) {
        bytes[i] = value;
    }

    return buffer;
}

void *my_memcpy(void *dest, const void *source, size_t size)
{
    const unsigned char *src_bytes = (const unsigned char *)source;
    unsigned char *dest_bytes = (unsigned char *)dest;

    size_t index = 0;

    while (index < size) {
        *dest_bytes = *src_bytes;

        src_bytes++;
        dest_bytes++;
        index++;
    }

    return dest;
}



void *my_memmove(void *dest, const void *source, size_t size)
{
    unsigned char *dest_bytes = (unsigned char *)dest;
    const unsigned char *src_bytes = (const unsigned char *)source;

    if (dest == source || size == 0) {
        return dest;
    }

    if ((uintptr_t)dest_bytes < (uintptr_t)src_bytes) {
        for (size_t i = 0; i < size; i++) {
            dest_bytes[i] = src_bytes[i];
        }
    } else {
        for (size_t i = size; i > 0; i--) {
            dest_bytes[i - 1] = src_bytes[i - 1];
        }
    }

    return dest;
}
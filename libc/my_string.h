#ifndef MY_STRING_H //header guards. oни защищают от ситуации, когда один и тот же .h случайно подключился несколько раз.
#define MY_STRING_H

char *my_strcpy(char *dest, int dest_capacity, const char *src);
int my_strlen(const char *src);
int my_strcmp(const char *str1, const char *str2);
void *my_memcpy(void *dest, const void *source, size_t size);
void *my_memmove(void *dest, const void *source, size_t size);

#endif
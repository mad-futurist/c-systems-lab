#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    int id;
    const char *name;
    const char *status;
    int priority;
} Task;

typedef struct {
    Task *arr;
    int capacity;
    int size;
} TaskList;

void print_task(const Task *t);
Task *find_task(int id, Task *arr, int arr_length);
Task *find_task_highest_prio(Task *arr, int arr_length);
int complete_task(int id, Task *arr, int arr_length);
int delete_task(int id, Task *arr, int arr_length);

int main(void)
{
    Task arr[] = {
        {1, "C code", "IN PROGRESS", 1},
        {2, "Make a cake", "DONE", 2},
        {3, "Print a document", "TODO", 1}
    };

    int arr_length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arr_length; i++) {
        print_task(arr + i);
        printf("\n");
    }

    Task *found_task = find_task_highest_prio(arr, arr_length);

    if (found_task != NULL) {
        found_task->status = "FOUND";
        print_task(found_task);
        printf("\n");
    }

    int result = complete_task(3, arr, arr_length);

    if (result == 0) {
        printf("Task completed\n");
    } else {
        printf("Task not found\n");
    }

    arr_length = delete_task(2, arr, arr_length);

    for (int i = 0; i < arr_length; i++) {
        print_task(arr + i);
        printf("\n");
    }
    int n;
    printf("Give me arr size: ");
    scanf("%d", &n);

    Task *arr_malloc = malloc(sizeof(Task) * n);

    return 0;
}

Task *find_task(int id, Task *arr, int arr_length)
{
    for (int i = 0; i < arr_length; i++) {
        if ((arr + i)->id == id) {
            return arr + i;
        }
    }

    return NULL;
}

Task *find_task_highest_prio(Task *arr, int arr_length)
{
    if (arr == NULL || arr_length == 0) {
        return NULL;
    }

    int max_prio = arr->priority;
    int index = 0;

    for (int i = 1; i < arr_length; i++) {
        Task *t = arr + i;

        if (t->priority > max_prio) {
            max_prio = t->priority;
            index = i;
        }
    }

    return arr + index;
}

int delete_task(int id, Task *arr, int arr_length)
{
    int index = -1;

    for (int i = 0; i < arr_length; i++) {
        if ((arr + i)->id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return arr_length;
    }

    for (int i = index; i < arr_length - 1; i++) {
        *(arr + i) = *(arr + i + 1);
    }

    arr[arr_length - 1] = (Task){0};

    return arr_length - 1;
}

int complete_task(int id, Task *arr, int arr_length)
{
    Task *t = find_task(id, arr, arr_length);

    if (t != NULL) {
        t->status = "DONE";
        return 0;
    }

    return 1;
}

void print_task(const Task *t)
{
    printf("%d %s %s %d",
           t->id,
           t->name,
           t->status,
           t->priority);
}
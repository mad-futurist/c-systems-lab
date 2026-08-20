#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
    const char *status;
    int priority;
} Task;

typedef struct {
    Task *arr;
    int capacity;
    int size;
} TaskList;

TaskList *init_tasklist(int capacity);
Task *create_task(int prio, const char *name, int id);
int add_task(Task *t, TaskList *tl);

void print_task(const Task *t);
void print_tasklist(const TaskList *tl);

void destroy_tasklist(TaskList *tl);

int main(void)
{
    int capacity;

    printf("Give me how many tasks do you have: ");
    scanf("%d", &capacity);

    TaskList *tl = init_tasklist(capacity);

    if (tl == NULL) {
        printf("Failed to create TaskList\n");
        return 1;
    }

    printf("Task list capacity: %d\n", tl->capacity);

    char name[256];
    int prio;

    printf("Give me your task and priority: ");
    scanf("%255s %d", name, &prio);

    Task *t = create_task(prio, name, tl->size);

    if (t == NULL) {
        destroy_tasklist(tl);
        return 1;
    }

    if (add_task(t, tl) == 0) {
        free(t);
    } else {
        free(t->name);
        free(t);
        printf("Task list is full\n");
    }

    print_tasklist(tl);

    destroy_tasklist(tl);

    return 0;
}

TaskList *init_tasklist(int capacity)
{
    if (capacity <= 0) {
        return NULL;
    }

    TaskList *taskList = malloc(sizeof(TaskList));

    if (taskList == NULL) {
        return NULL;
    }

    taskList->arr = malloc(sizeof(Task) * capacity);

    if (taskList->arr == NULL) {
        free(taskList);
        return NULL;
    }

    taskList->capacity = capacity;
    taskList->size = 0;

    return taskList;
}

Task *create_task(int prio, const char *name, int id)
{
    Task *t = malloc(sizeof(Task));

    if (t == NULL) {
        return NULL;
    }

    t->name = malloc(strlen(name) + 1);

    if (t->name == NULL) {
        free(t);
        return NULL;
    }

    strcpy(t->name, name);

    t->priority = prio;
    t->id = id;
    t->status = "TODO";

    return t;
}

int add_task(Task *t, TaskList *tl)
{
    if (tl->size < tl->capacity) {
        tl->arr[tl->size] = *t;
        tl->size++;

        return 0;
    }

    return 1;
}

void print_task(const Task *t)
{
    printf("| %d | %s | %s | %d |",
           t->id,
           t->name,
           t->status,
           t->priority);
}

void print_tasklist(const TaskList *tl)
{
    for (int i = 0; i < tl->size; i++) {
        print_task(tl->arr + i);
        printf("\n");
    }
}

void destroy_tasklist(TaskList *tl)
{
    if (tl == NULL) {
        return;
    }

    for (int i = 0; i < tl->size; i++) {
        free(tl->arr[i].name);
    }

    free(tl->arr);
    free(tl);
}
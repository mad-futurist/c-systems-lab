#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "../libc/my_string.h"

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
    int next_id;
} TaskList;

TaskList *init_tasklist(int capacity);
int expand_list(TaskList *tl);
int add_task(Task *t, TaskList *tl);
Task *find_task(TaskList *tl, int id);
int delete_task(TaskList *tl, int id);
void destroy_tasklist(TaskList *tl);

Task *create_task(int prio, const char *name, int id);

void print_task(const Task *t);
void print_tasklist(const TaskList *tl);


int main(void)
{
    int capacity;

    printf("Give me initial task list capacity: ");

    if (scanf("%d", &capacity) != 1) {
        printf("Invalid capacity\n");
        return 1;
    }

    TaskList *tl = init_tasklist(capacity);

    if (tl == NULL) {
        printf("Failed to create TaskList\n");
        return 1;
    }

    printf("Task list capacity: %d\n", tl->capacity);

    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    char name[256];

    printf("Give me your task: ");

    if (fgets(name, sizeof(name), stdin) == NULL) {
        destroy_tasklist(tl);
        return 1;
    }
    size_t name_length = my_strlen(name);

    if (name_length > 0 && name[name_length - 1] == '\n') {
        name[name_length - 1] = '\0';
    }

    int prio;

    printf("Give me priority: ");

    if (scanf("%d", &prio) != 1) {
        printf("Invalid priority\n");
        destroy_tasklist(tl);
        return 1;
    }

    Task *t = create_task(
        prio,
        name,
        tl->next_id
    );

    if (t == NULL) {
        printf("Failed to create task\n");
        destroy_tasklist(tl);
        return 1;
    }

    if (add_task(t, tl) == 0) {

        free(t);

        tl->next_id++;
    }
    else {

        free(t->name);
        free(t);

        printf("Failed to add task\n");
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
    taskList->next_id = 0;

    return taskList;
}


Task *create_task(int prio, const char *name, int id)
{
    Task *t = malloc(sizeof(Task));

    if (t == NULL) {
        return NULL;
    }

    size_t name_length = my_strlen(name);

    t->name = malloc(name_length + 1);

    if (t->name == NULL) {
        free(t);
        return NULL;
    }

    if (my_strcpy(
            t->name,
            name_length + 1,
            name
        ) == NULL) {

        free(t->name);
        free(t);

        return NULL;
    }

    t->priority = prio;
    t->id = id;
    t->status = "TODO";

    return t;
}


int add_task(Task *t, TaskList *tl)
{
    if (t == NULL || tl == NULL) {
        return 1;
    }

    if (tl->size >= tl->capacity) {

        if (expand_list(tl) != 0) {
            return 1;
        }
    }

    tl->arr[tl->size] = *t;
    tl->size++;

    return 0;
}


int expand_list(TaskList *tl)
{
    if (tl == NULL) {
        return 1;
    }

    int new_capacity = tl->capacity * 2;

    Task *new_arr = realloc(
        tl->arr,
        sizeof(Task) * new_capacity
    );

    if (new_arr == NULL) {
        return 1;
    }

    tl->arr = new_arr;
    tl->capacity = new_capacity;

    return 0;
}


Task *find_task(TaskList *tl, int id)
{
    if (tl == NULL) {
        return NULL;
    }
    for (int i = 0; i < tl->size; i++) {

        if (tl->arr[i].id == id) {
            return tl->arr + i;
        }
    }
    return NULL;
}


int delete_task(TaskList *tl, int id)
{
    if (tl == NULL || tl->size == 0) {
        return 1;
    }

    int index = -1;

    for (int i = 0; i < tl->size; i++) {

        if (tl->arr[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return 1;
    }

    free(tl->arr[index].name);
    for (int i = index; i < tl->size - 1; i++) {
        tl->arr[i] = tl->arr[i + 1];
    }

    tl->size--;
    tl->arr[tl->size] = (Task){0};

    return 0;
}


void print_task(const Task *t)
{
    if (t == NULL) {
        return;
    }

    printf(
        "| %d | %s | %s | %d |",
        t->id,
        t->name,
        t->status,
        t->priority
    );
}


void print_tasklist(const TaskList *tl)
{
    if (tl == NULL) {
        return;
    }

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
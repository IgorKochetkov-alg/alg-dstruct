#pragma once
#include <limits.h>
#define INVALID_PTR (void*)INT_MAX

typedef struct List
{
    struct List* next;
    int length;
    char* data;
} List;

struct List* CreateList();

struct List* CreateNewElement(List* curr_element);

struct List* FindElement(List* head, char* str, int length);

int DataOutput(List* head);

int WordSort();

char* CreateBuffer(FILE* file);
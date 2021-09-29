#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "Task 3.1.2.h"

struct List* CreateList()
{
    struct List* head;
    head = (struct List*)malloc(sizeof(List));
    if (head == NULL)
    {
        return INVALID_PTR;
    }
    head->data = NULL;
    head->length = 0;
    head->next = NULL;
    return head;
}

char* CreateBuffer(FILE* file)
{
    if (file == NULL)
    {
        return INVALID_PTR;
    }
    char* buffer = NULL;
    char sym;
    int max = 0;
    int length = 0;

    do
    {
        sym = fgetc(file);
        if (((sym == ' ') || (sym == '\n') || (sym == EOF)) && (length != 0))
        {
            if (length > max)
            {
                max = length;
            }
            length = 0;
        }
        else
        {
            if ((sym != ' ') && (sym != '\n') && (sym != EOF))
            {
                length++;
            }
        }
    } while (sym != EOF);
    if (max == 0)
    {
        return INVALID_PTR;
    }
    buffer = (char*)calloc(max + 1, sizeof(char));
    if (buffer == NULL)
    {
        return INVALID_PTR;
    }
    fseek(file, 0, SEEK_SET);
    return buffer;
}

struct List* CreateNewElement(List* curr_element)
{
    struct List* new_element = NULL;
    new_element = (struct List*)malloc(sizeof(List));
    if (new_element == NULL)
    {
        return INVALID_PTR;
    }
    if (curr_element != NULL)
    {
        new_element->next = curr_element->next;
        curr_element->next = new_element;
    }
    new_element->data = NULL;
    new_element->length = 0;
    return new_element;
}

struct List* FindElement(List* head, char* str, int length)
{
    if ((head == NULL) || (str == NULL) || (length <= 0))
    {
        return INVALID_PTR;
    }

    List* prev_el = NULL;
    List* curr_el = NULL;
    curr_el = head;

    do
    {

        if (curr_el->length > length)
        {
            if (curr_el->next != NULL)
            {
                prev_el = curr_el;

                curr_el = curr_el->next;
            }
            else
            {
                return curr_el;
            }
        }
        if (curr_el->length == length)
        {
            if (strcmp(curr_el->data, str) >= 0)
            {
                return prev_el;
            }
            else
            {
                prev_el = curr_el;

                curr_el = curr_el->next;
            }
        }
        if (curr_el->length < length)
        {
            if (curr_el->next == NULL)
            {
                return NULL;
            }
            else
            {
                return prev_el;
            }
        }
    } while (curr_el != NULL);
}

int DataOutput(List* head)
{
    if (head == NULL)
    {
        return 1;
    }
    setlocale(LC_ALL, "Russian");
    int n = 0;
    int choice = 0;
    struct List* temp = NULL;
    temp = head;

    printf("Введите 1, чтобы вывести слова длиной>N или 2, чтобы вывести слова длины N\n");
    scanf("%d", &choice);

    printf("Введите число N\n");
    scanf("%d", &n);
    
    while (temp != NULL)
    {
        switch (choice)
        {
        case 1:
        {
            if (temp->length > n)
            {
                printf("%s\n", temp->data);
            }
        } break;
        case 2:
        {
            if (temp->length == n)
            {
                printf("%s\n", temp->data);
            }
        } break;
        }
        temp = temp->next;
    }
    return 0;
}

int WordSort()
{
    FILE* file;
    List* head = NULL;
    List* found_el = NULL;
    List* curr_el;
    char* buffer = NULL;
    char sym;
    int length = 0;

    file = fopen("input.txt", "r");

    head = CreateList();
    buffer = CreateBuffer(file);

    if (buffer == INVALID_PTR)
    {
        return 1;
    }

    do
    {
        sym = fgetc(file);

        if (((sym == ' ') || (sym == '\n') || (sym == EOF)) && (length != 0))
        {
            if (head->length == 0)
            {
                head->length = length;
                head->data = (char*)calloc(length + 1, sizeof(char));
                strncpy(head->data, buffer, length);
            }
            else
            {
                found_el = FindElement(head, buffer, length);
                if (found_el == INVALID_PTR)
                {
                    return 2;
                }
                if (found_el == NULL)
                {
                    found_el = head;
                    head = CreateNewElement(NULL);
                    if (head == INVALID_PTR)
                    {
                        return 2;
                    }
                    head->next = found_el;
                    curr_el = head;
                }
                else
                {
                    curr_el = CreateNewElement(found_el);
                    if (curr_el == INVALID_PTR)
                    {
                        return 2;
                    }
                }
                curr_el->length = length;
                curr_el->data = (char*)calloc(length + 1, sizeof(char));
                strncpy(curr_el->data, buffer, curr_el->length);

            }
            memset(buffer, 0, length);
            length = 0;
        }
        else
        {
            if ((sym != ' ') && (sym != '\n') && (sym != EOF))
            {
                length++;
                strncat(buffer, &sym, 1);
            }
        }
    } while (sym != EOF);

    DataOutput(head);
    fclose(file);
    return 0;
}

//int main(void)
//{
//    WordSort();
//}

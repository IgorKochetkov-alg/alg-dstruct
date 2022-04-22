#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 7369
#define CONST_1 7369
#define CONST_2 1181

#define FILLED 1
#define EMPTY 0

typedef struct HashMapNode
{
	int key;
	char* str;
	int status;
} HashMapNode;

typedef struct HashMap
{
	int size;
	HashMapNode* nodes;
} HashMap;


char* copyStr(char* str)
{
	int length = strlen(str) + 1;

	char* newStr = (char*)malloc(length * sizeof(char));

	if (newStr == NULL)
	{
		return NULL;
	}

	newStr[length - 1] = '\0';
	strcpy(newStr, str);

	return newStr;
}

HashMap* CreateNewMap(int size)
{
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));

	if (map == NULL)
	{
		return NULL;
	}

	map->size = size;
	map->nodes = (HashMapNode*)calloc(size, sizeof(HashMapNode));

	if (map->nodes == NULL)
	{
		free(map);

		return NULL;
	}

	return map;
}

int Find(HashMap* map, int key)
{
	int x = key % CONST_1;
	int y = 1 + (key % CONST_2);
	int index = 0;

	for (int i = 0; i < map->size; i++)
	{
		index = (x + i * y) % (map->size);
		HashMapNode* node = &map->nodes[index];

		if (node->key == key)
		{
			if (node->status == FILLED)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

void Add(HashMap* map, int key, char* str)
{
	int x = key % CONST_1;
	int y = 1 + (key % CONST_2);
	int index = 0;

	if (Find(map, key) == 1)
	{
		return;
	}
	else
	{
		for (int i = 0; i < map->size; i++)
		{
			index = (x + i * y) % (map->size);
			HashMapNode* node = &map->nodes[index];

			if (node->status == EMPTY)
			{
				node->status = FILLED;
				node->key = key;
				node->str = copyStr(str);
				return;
			}
		}
	}

	return;
}

void Remove(HashMap* map, int key)
{
	int x = key % CONST_1;
	int y = 1 + (key % CONST_2);
	int index = 0;

	for (int i = 0; i < map->size; i++)
	{
		index = (x + i * y) % (map->size);
		HashMapNode* node = &map->nodes[index];

		if (node->key == key)
		{
			if (node->status == FILLED)
			{
				node->status = EMPTY;
				free(node->str);
				return;
			}
			else
			{
				return;
			}
		}
	}
}

int main() 
{
	char sym;
	int key;
	HashMap* map = CreateNewMap(SIZE);

	while (fscanf(stdin, "%c %d", &sym, &key) > 0)
	{
		if (sym == 'a')
		{
			Add(map, key, "stroka");
		}

		if (sym == 'r')
		{
			Remove(map, key);
		}

		if (sym == 'f')
		{
			if (Find(map, key) == 1)
			{
				printf("yes\n");
			}
			else
			{
				printf("no\n");
			}
		}
	}

	return 0;
}
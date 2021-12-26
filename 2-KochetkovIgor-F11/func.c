#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
	int num;
	int value;
	struct Tree* left;
	struct Tree* right;
} Tree;

void AddElement(Tree* root, int value)
{
	if (root == NULL)
	{
		fprintf(stderr, "Error");
		return;
	}

	Tree* newElement = (Tree*)malloc(sizeof(Tree));

	if (newElement == NULL)
	{
		fprintf(stderr, "Error");
		return;
	}

	newElement->left = NULL;
	newElement->right = NULL;
	newElement->num = 0;
	newElement->value = value;

	Tree* tmpRoot = root;

	while (tmpRoot != NULL)
	{
		tmpRoot->num = tmpRoot->num + 1;

		if (tmpRoot->left == NULL)
		{
			tmpRoot->left = newElement;
			return;
		}
		else if (tmpRoot->right == NULL)
		{
			tmpRoot->right = newElement;
			return;
		}

		if (tmpRoot->left->num <= tmpRoot->right->num)
		{
			tmpRoot = tmpRoot->left;
		}
		else
		{
			tmpRoot = tmpRoot->right;
		}
	}
}

Tree* SearchElement(Tree* root, int value)
{
	Tree** way = (Tree**)calloc(root->num + 1, sizeof(Tree*));
	way[0] = root;

	int nextNum = 1;
	int oldNum = 0;

	Tree* tmp = NULL;

	while (oldNum < root->num + 1)
	{
		if (way[oldNum]->value == value)
		{
			tmp = way[oldNum];
			break;
		}

		if (way[oldNum]->left != NULL)
		{
			way[nextNum] = way[oldNum]->left;
			nextNum++;
		}

		if (way[oldNum]->right != NULL)
		{
			way[nextNum] = way[oldNum]->right;
			nextNum++;
		}

		oldNum++;
	}

	if ((tmp == NULL) || (tmp == root))
	{
		return NULL;
	}

	for (int i = 0; i < 1 + root->num; i++)
	{
		if ((way[i]->left == tmp) || (way[i]->right == tmp))
		{
			tmp = way[i];
			break;
		}
	}

	return tmp;
}

void DeleteElement(Tree* root, int value)
{
	if (root == NULL)
	{
		fprintf(stderr, "Error");
		return;
	}

	Tree* tmpRoot = SearchElement(root, value);

	if (tmpRoot == NULL)
	{
		if (root->value == value)
		{
			fprintf(stderr, "Main root can't be deleted");
			return;
		}
		else
		{
			fprintf(stderr, "Node was not found");
			return;
		}
	}
	else
	{
		Tree* tmp = tmpRoot;
		if (tmpRoot->left->value == value)
		{
			tmpRoot = tmpRoot->left;
			tmp->left = NULL;
		}
		else
		{
			tmpRoot = tmpRoot->right;
			tmp->right = NULL;
		}
	}

	Tree** delete = (Tree**)calloc(tmpRoot->num + 1, sizeof(Tree*));

	delete[0] = tmpRoot;

	int nextNum = 1;
	int oldNum = 0;

	while (oldNum < tmpRoot->num)
	{
		if (delete[oldNum]->left != NULL)
		{
			delete[nextNum] = delete[oldNum]->left;
			nextNum++;
		}

		if (delete[oldNum]->right != NULL)
		{
			delete[nextNum] = delete[oldNum]->right;
			nextNum++;
		}

		oldNum++;
	}

	for (int i = tmpRoot->num; i >= 0; i--)
	{
		free(delete[i]);
	}

	return;
}

int main()
{
	Tree* mainRoot = NULL;

	mainRoot = (Tree*)malloc(sizeof(Tree));

	if (mainRoot == NULL)
	{
		return 1;
	}

	mainRoot->left = NULL;
	mainRoot->right = NULL;
	mainRoot->num = 0;
	mainRoot->value = 0;

	AddElement(mainRoot, 1);
	AddElement(mainRoot, 2);
	AddElement(mainRoot, 3);
	AddElement(mainRoot, 4);
	AddElement(mainRoot, 5);

	DeleteElement(mainRoot, 5);
	DeleteElement(mainRoot, 2);

	return 0;
}
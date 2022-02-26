#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM 1000

typedef struct Treap
{
	int size;
	int priority;
	int value;
	struct Treap* left;
	struct Treap* right;
} Treap;

typedef struct TwinTreaps
{
	struct Treap* right;
	struct Treap* left;
} TwinTreaps;

//+
Treap* CreateNode(int value)
{
	Treap* newNode = (Treap*)malloc(sizeof(Treap));

	if (newNode == NULL)
	{
		return NULL;
	}

	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->size = 1;
	newNode->priority = rand();

	return newNode;
}
//+
int GetTreeSize(Treap* tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	else
	{
		return tree->size;
	}
}
//+
void UpdateTreeSize(Treap* tree)
{
	if (tree == NULL)
	{
		return;
	}

	tree->size = 1 + GetTreeSize(tree->left) + GetTreeSize(tree->right);
	return;
}
//+
Treap* Merge(Treap* tree1, Treap* tree2)
{
	if (tree1 == NULL)
	{
		return tree2;
	}

	if (tree2 == NULL)
	{
		return tree1;
	}

	if (tree1->priority > tree2->priority)
	{
		tree1->right = Merge(tree1->right, tree2);
		UpdateTreeSize(tree1);
		return tree1;
	}
	else
	{
		tree2->left = Merge(tree1, tree2->left);
		UpdateTreeSize(tree2);
		return tree2;
	}
}
//+
TwinTreaps Split(Treap* tree, int k)
{
	if (tree == NULL)
	{
		TwinTreaps pair = { NULL, NULL };
		return pair;
	}

	if (GetTreeSize(tree->left) < k)
	{
		TwinTreaps pair = Split(tree->right, k - GetTreeSize(tree->left) - 1);
		tree->right = pair.left;
		UpdateTreeSize(tree);
		pair.left = tree;
		return pair;
	}
	else
	{
		TwinTreaps pair = Split(tree->left, k);
		tree->left = pair.right;
		UpdateTreeSize(tree);
		pair.right = tree;
		return pair;
	}
}
//+
Treap* Add(Treap* tree, int pos, int value)
{
	TwinTreaps result = Split(tree, pos);
	Treap* newTreap = CreateNode(value);

	if (newTreap == NULL) 
	{
		return NULL;
	}

	return Merge(Merge(result.left, newTreap), result.right);
}
//+
Treap* Remove(Treap* tree, int pos)
{
	if (tree == NULL)
	{
		return NULL;
	}

	TwinTreaps result1 = Split(tree, pos);
	TwinTreaps result2 = Split(result1.right, 1);
	tree = Merge(result1.left, result2.right);

	free(result2.left);

	return tree;
}

Treap* FindElement(Treap* tree, int value)
{
	Treap* result = NULL;

	if (tree == NULL)
	{
		return NULL;
	}

	if (tree->value == value)
	{
		return tree;
	}

	result = FindElement(tree->left, value);

	if (result != NULL)
	{
		return result;
	}

	result = FindElement(tree->right, value);

	if (result != NULL)
	{
		return result;
	}
	else
	{
		return NULL;
	}
}

void DestroyTree(Treap* tree)
{
	if (tree != NULL)
	{
		DestroyTree(tree->left);
		DestroyTree(tree->right);
		free(tree);
	}

	return;
}

void FindIndex(Treap* tree, int value, int* num, int* flag)
{
	if ((tree != NULL) && (*flag == 0))
	{
		FindIndex(tree->left, value, num, flag);

		if (*flag == 0)
		{
			if (tree->value != value)
			{
				(*num)++;
			}
			else
			{
				(*flag) = 1;
				return;
			}
		}

		FindIndex(tree->right, value, num, flag);
	}
}

int main() 
{
	char sym;
	int val;
	Treap* tree = NULL;

	while (fscanf(stdin, "%c %d", &sym, &val) > 0) 
	{
		Treap* check = NULL;

		if (sym == 'a') 
		{
			check = FindElement(tree, val);

			if (check == NULL)
			{
				tree = Add(tree, 0, val);
			}
		}

		if (sym == 'r') 
		{
			int flag = 0;
			int pos = 0;
			FindIndex(tree, val, &pos, &flag);

			if (flag != 0)
			{
				tree = Remove(tree, pos);
			}
		}

		if (sym == 'f') 
		{
			check = FindElement(tree, val);

			if (check == NULL)
			{
				fprintf(stdout, "no\n");
			}
			else
			{
				fprintf(stdout, "yes\n");
			}
		}
	}

	DestroyTree(tree);

	return 0;
}
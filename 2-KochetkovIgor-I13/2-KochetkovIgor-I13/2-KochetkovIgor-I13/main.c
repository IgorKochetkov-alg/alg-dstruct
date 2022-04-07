#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

#define T 5 
#define MAX (2 * T)
#define MAX_CHILDREN (2 * T + 1) 

typedef struct BPlusTree
{
	int leaves;
	int length;
	int keys[MAX];
	struct BPlusTree* left;
	struct BPlusTree* right;
	struct BPlusTree* parent;
	struct BPlusTree* children[MAX_CHILDREN];

} BPTree;

BPTree* CreateBPlusTree()
{
    BPTree* newTree = (BPTree*)(malloc(sizeof(BPTree)));

    if (newTree == NULL)
    {
        return NULL;
    }

    newTree->leaves = 0;
    newTree->length = 0;
    newTree->parent = NULL;
    newTree->left = NULL;
    newTree->right = NULL;

    for (int i = 0; i <= MAX; i++)
    {
        newTree->children[i] = NULL;
    }
        
    return newTree;
}

BPTree* FindNode(BPTree* tree, int key) 
{
    if (tree == NULL)
    {
        return NULL;
    }

    int i = 0;
    BPTree* node = tree;

    while (node->leaves == 1)
    {
        for (i = 0; i <= node->length; i++) 
        {
            if ((i == node->length) || (key < node->keys[i]))
            {
                node = node->children[i];
                break;
            }
        }
    }
        
    return node;
}

int Find(BPTree* tree, int key) 
{
    BPTree* newTree = FindNode(tree, key);

    if (tree != NULL) 
    {
        for (int i = 0; i < newTree->length; i++)
        {
            if (newTree->keys[i] == key)
            {
                return 1;
            }
        }
    }

    return 0;
}

int FindMinimum(BPTree* tree) 
{
    for (int i = 0; i < MAX; i++)
    {
        if (tree->children[i])
        {
            return FindMinimum(tree->children[i]);
        }
    }
        
    return tree->keys[0];
}

void Update(BPTree* node, int key) 
{
    BPTree* newTree = node->parent;
    int i = 0;

    while (newTree != NULL) 
    {
        while ((i < newTree->length) && (newTree->keys[i] < key))
        {
            i++;
        }
            
        if (i < newTree->length)
        {
            if (newTree->keys[i] != FindMinimum(newTree->children[i + 1]))
            {
                newTree->keys[i] = FindMinimum(newTree->children[i + 1]);
            }
        }
            
        newTree = newTree->parent;
    }

    return;
}

void Split(BPTree** root, BPTree* node) 
{
    int key = 0;
    int pos = 0;

    BPTree* newTree = CreateBPlusTree();
    newTree->leaves = 1;

    if (node->right != NULL) 
    {
        newTree->right = node->right;
        node->right->left = newTree;
        node->right = newTree;
        newTree->left = node;
    }
    else 
    {
        newTree->right = node->right;
        node->right = newTree;
        newTree->left = node;
    }

    key = node->keys[T];
    newTree->length = T - 1;
    node->length = T;

    for (int i = 0; i < newTree->length; i++)
    {
        newTree->keys[i] = node->keys[i + T + 1];
        newTree->children[i] = node->children[i + T + 1];
        node->children[i + T + 1] = NULL;
    }

    newTree->children[newTree->length] = node->children[MAX];
    node->children[MAX] = NULL;

    if (node->leaves == 0) 
    {
        newTree->length++;
        newTree->leaves = 0;

        for (int i = newTree->length - 1; i >= 1; i--)
        {
            newTree->keys[i] = newTree->keys[i - 1];

        }

        newTree->keys[0] = node->keys[T];
    }

    if (node == *(root)) 
    {
        (*root) = (BPTree*)malloc(sizeof(BPTree));

        if ((*root) == NULL)
        {
            return;
        }

        (*root)->keys[0] = key;
        (*root)->children[0] = node;
        (*root)->children[1] = newTree;

        for (int i = 0; i < MAX_CHILDREN; i++)
        {
            if (newTree->children[i] != NULL)
            {
                newTree->children[i]->parent = newTree;
            }

            if (node->children[i] != NULL)
            {
                node->children[i]->parent = node;
            }
        }

        (*root)->leaves = 1;
        (*root)->parent = NULL;
        (*root)->left = NULL;
        (*root)->right = NULL;

        for (int i = 2; i < MAX_CHILDREN; i++)
        {
            (*root)->children[i] = NULL;
        }
            
        (*root)->length = 1;
        node->parent = (*root);
        newTree->parent = (*root);
    }
    else 
    {
        newTree->parent = node->parent;

        while ((pos < node->parent->length) && (node->parent->keys[pos] < key))
        {
            pos++;
        }

        for (int i = node->parent->length; i >= pos; i--)
        {
            node->parent->keys[i] = node->parent->keys[i - 1];
        }

        for (int i = node->parent->length + 1; i >= pos + 2; i--)
        {
            node->parent->children[i] = node->parent->children[i - 1];
        }

        for (int i = 0; i < 2 * T; i++)
        {
            if (newTree->children[i] != NULL)
            {
                newTree->children[i]->parent = newTree;
            }
        }
            
        node->parent->keys[pos] = key;
        node->parent->children[pos + 1] = newTree;
        node->parent->length++;

        if (node->parent->length == MAX)
        {
            Split(root, node->parent);
        }
    }

    return;
}

void Merge(BPTree* tree, BPTree* node, int key) 
{
    BPTree* parent = node->parent;
    BPTree* right = node->right;
    BPTree* left = node->left;
    BPTree* tmp = NULL;

    if ((right != NULL) && (right->parent == node->parent)) 
    {
        for (int i = 0; i < right->length; i++) 
        {
            node->keys[node->length] = right->keys[i];
            node->children[node->length + 1] = right->children[i];

            if (right->children[i] != NULL)
            {
                right->children[i]->parent = node;
            }

            node->length++;
        }

        node->children[node->length + 1] = right->children[right->length];

        if (right->children[right->length])
        {
            right->children[right->length]->parent = node;
        }

        if (right->right)
        {
            right->right->left = node;
        }

        node->right = right->right;

        DeleteFromNode(tree, node->parent, FindMinimum(right));
        Update(node, key);
    }
    else 
    {
        for (int  i = 0; i < node->length; i++) 
        {
            left->keys[left->length] = node->keys[i];
            left->children[left->length + 1] = node->children[i];

            if (node->children[i] != NULL)
            {
                node->children[i]->parent = left;
            }

            left->length++;
        }

        left->children[left->length + 1] = node->children[node->length];

        if (node->children[node->length])
        {
            node->children[node->length]->parent = left;

        }

        left->right = node->right;

        if (node->right != NULL)
        {
            node->right->left = left;
        }

        DeleteFromNode(tree, left->parent, FindMinimum(node));
        Update(left, key);
    }
    return;
}

void Add(BPTree** root, int key)
{
    BPTree* leaf = FindNode((*root), key);

    if (leaf == NULL)
    {
        return;
    }

    int pos = 0;

    for (int i = 0; i < leaf->length; i++) 
    {
        if (leaf->keys[i] == key)
        {
            return;
        }
    }

    while (pos < leaf->length && leaf->keys[pos] < key)
    {
        ++pos;
    }

    for (int i = leaf->length; i >= pos + 1; i--)
    {
        leaf->keys[i] = leaf->keys[i - 1];
    }

    leaf->keys[pos] = key;
    leaf->length++;

    if (leaf->length == MAX)
    {
        Split(root, leaf);
    }

    return;
}

void DeleteFromNode(BPTree* tree, BPTree* node, int key) 
{
    int i = 0;
    int pos = 0;

    while ((pos < node->length) && (node->keys[pos] < key))
    {
        pos++;
    }

    for (int i = pos; i < node->length; i++)
    {
        node->keys[i] = node->keys[i + 1];
    }

    for (int i = pos + 1; i <= node->length; i++)
    {
        node->children[i] = node->children[i + 1];
    }
        
    for (int i = node->length + 1; i < MAX_CHILDREN; i++)
    {
        *(node->children + i) = NULL;
    }
        
    node->length--;

    if (node == tree) 
    {
        for (int i = 0; i < 2 * T + 1; i++)
        {
            if (node->children[i] != NULL)
            {
                if (node->children[i]->length == 0)
                {
                    node->children[i] = NULL;
                }
            }
        }
            
        if ((tree->length == 0) && (tree->children[0] != NULL))
        {
            tree = tree->children[0];
        }

        return;
    }

    if (node->length >= 1)
    {
        Update(node, key);
    }
    else
    {
        if (node->length < T - 1) 
        {
            BPTree* right = node->right;
            BPTree* left = node->left;

            if ((left != NULL) && (left->length > (T - 1)) && (left->parent == node->parent)) 
            {
                left->length--;
                node->length++;

                for (int i = 1; i < node->length; i++) 
                {
                    node->keys[i] = node->keys[i - 1];
                    node->children[i] = node->children[i - 1];
                }

                node->children[node->length] = node->children[node->length - 1];
                node->keys[0] = left->keys[left->length];
                node->children[0] = left->children[left->length + 1];
                left->children[left->length + 1] = NULL;

                if (node->children[0] != NULL)
                {
                    node->children[0]->parent = node;
                }

                Update(node, key);
            }
            else
            {
                if ((right != NULL) && (right->length > (T - 1)) && (right->parent == node->parent)) 
                {
                    node->length++;
                    node->keys[node->length - 1] = right->keys[0];
                    node->children[node->length] = right->children[0];

                    if (node->children[node->length] != NULL)
                    {
                        node->children[node->length]->parent = node;
                    }

                    for (int i = 0; i < right->length; i++) 
                    {
                        right->keys[i] = right->keys[i + 1];
                        right->children[i] = right->children[i + 1];
                    }

                    for (int i = 0; i < 2 * T; i++)
                    {
                        if ((right->children[i] == right->children[i + 1]) && (right->children[i] != NULL)) 
                        {
                            right->children[i + 1] = NULL;
                            break;
                        }
                    }
                        
                    right->length--;
                    Update(node, key);
                }
                else
                {
                    Merge(tree, node, key);
                }
            } 
        }
    }
        
    return;
}

void Remove(BPTree* tree, int key) 
{
    if (tree == NULL)
    {
        return;
    }

    if (Find(tree, key) == 0)
    {
        return;
    }

    BPTree* leaf = FindNode(tree, key);
    DeleteFromNode(tree, leaf, key);

    return;
}

void Print(BPTree* tree, int pos, int child) 
{
    if (tree != NULL) 
    {
        for (int i = 0; i < tree->length; i++)
        {
            printf("lvl %i child %i key %i\n", pos, child, tree->keys[i]);
        }

        for (int i = 0; i < MAX; i++) 
        {
            if (tree->children[i])
            {
                Print(tree->children[i], pos + 1, i);
            }
        }
    }

    return;
}

void DestroyTree(BPTree* tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->leaves == 1)
    {
        for (int i = 0; i <= tree->length; i++)
        {
            DestroyTree(tree->children[i]);
        }    
    }

    free(tree);
    return;
}

int main()
{
	char sym;
	int key;
	BPTree* tree = CreateBPlusTree();

	while (fscanf(stdin, "%c %d", &sym, &key) > 0)
	{
		if (sym == 'a')
		{
            Add(&tree, key);
		}

		if (sym == 'r')
		{
            Remove(tree, key);
		}

		if (sym == 'f')
		{
            if (Find(tree, key) == 1) 
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
		}
	}

	DestroyTree(tree);

	return 0;
}


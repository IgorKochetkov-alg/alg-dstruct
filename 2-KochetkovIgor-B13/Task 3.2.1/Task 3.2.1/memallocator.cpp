#include <stdio.h>
#include "memallocator.h"
#include <limits.h>

#define ALLOCATED 1
#define FREE 0

struct List
{
	struct List* prev;
	struct List* next;
	size_t size;
	char status;
};


List* head = NULL;
struct List* curPtr = NULL;
size_t blockSize = 0;

inline void* __MemBlockPtr(struct List* blockPtr)
{
	return (void*)(blockPtr + 1);
}

struct List* FindNextFit(size_t size)
{
	if (head == NULL)
	{
		return NULL;
	}

	struct List* ptr = curPtr;

	while (ptr != NULL)
	{
		if ((ptr->size >= size) && (ptr->status == FREE))
		{
			curPtr = ptr;
			return ptr;
		}

		ptr = ptr->next;
	}

	ptr = head;
	while (ptr != curPtr)
	{
		if ((ptr->size >= size) && (ptr->status == FREE))
		{
			curPtr = ptr;
			return ptr;
		}

		ptr = ptr->next;
	}

	return NULL;
}

void* AddNewBlock(struct List* foundBlock, size_t size)
{
	if (head == NULL)
	{
		return NULL;
	}

	if (foundBlock == NULL)
	{
		return NULL;
	}

	if (foundBlock->status == ALLOCATED)
	{
		return NULL;
	}

	if (foundBlock->size - size > sizeof(List))
	{
		struct List* newBlock = (struct List*)((char*)__MemBlockPtr(foundBlock) + size);

		newBlock->size = foundBlock->size - size - sizeof(struct List);
		newBlock->status = FREE;
		newBlock->next = foundBlock->next;
		newBlock->prev = foundBlock;
		if (foundBlock->next != NULL)
		{
			foundBlock->next->prev = newBlock;
		}
		foundBlock->next = newBlock;
	}
	
	foundBlock->size = size;
	foundBlock->status = ALLOCATED;

	return __MemBlockPtr(foundBlock);
}

struct List* FindPtr(void* cellPtr)
{
	struct List* foundBlock = (struct List*)cellPtr - 1;
	struct List* curBlock = head;

	while (curBlock != NULL)
	{
		if (curBlock == foundBlock)
		{
			return foundBlock;
		}

		curBlock = curBlock->next;
	}

	return NULL;
}

int meminit(void* pMemory, int size)
{
	if (head != NULL)
	{
		return 1;
	}

	if (size < sizeof(struct List))
	{
		return 2;
	}

	if (pMemory == NULL)
	{
		return 3;
	}

	head = (struct List*)pMemory;

	head->size = size - sizeof(struct List);
	head->next = NULL;
	head->prev = NULL;
	head->status = FREE;

	curPtr = head;

	blockSize = size;

	return 0;
}

void memdone()
{
	size_t curFreeSize = 0;

	if (head == NULL)
	{
		return;
	}

	struct List* checkPtr = head;

	while (checkPtr != NULL)
	{
		if (checkPtr->status == FREE)
		{
			curFreeSize += checkPtr->size;
		}
		checkPtr = checkPtr->next;
	}

	curFreeSize += sizeof(struct List);

	if (curFreeSize < blockSize)
	{
		fprintf(stderr, "Memory leak (expected %d,current %d)\n", blockSize, curFreeSize);
	}
}

void* memalloc(int size)
{
	if (head == NULL)
	{
		return NULL;
	}

	struct List* destBlockPtr = FindNextFit(size);
	if (destBlockPtr == NULL)
	{
		fprintf(stderr, "Block not found, not enough space\n");

		return 0;
	}

	void* memBlockPtr = AddNewBlock(destBlockPtr, size);
	if (memBlockPtr == NULL)
	{
		return 0;
	}

	return memBlockPtr;
}

void memfree(void* p)
{
	if (p == NULL)
	{
		return;
	}

	struct List* deleteBlock = FindPtr(p);
	if (deleteBlock == NULL)
	{
		fprintf(stderr, "Memory free: Invalid pointer, can't find block\n");

		return;
	}

	if (deleteBlock->status == FREE)
	{
		fprintf(stderr, "Memfree: block isn't allocated\n");
		
		return;
	}

	struct List* mergeBlock = deleteBlock;
	mergeBlock->status = FREE;

	if (deleteBlock->prev != NULL)
	{
		if (deleteBlock->prev->status == FREE)
		{
			if (deleteBlock == curPtr)
			{
				curPtr = deleteBlock->prev;
			}

			deleteBlock->status = FREE;
			size_t mergeSize = 0;
			if (deleteBlock->next != NULL)
			{
				mergeSize = (char*)deleteBlock->next - (char*)(deleteBlock->prev + 1);
			}
			else
			{
				mergeSize = (char*)(head + 1) + blockSize - (char*)(deleteBlock->prev + 1);
			}
			
			deleteBlock->prev->next = deleteBlock->next;
			if (deleteBlock->next != NULL)
			{
				deleteBlock->next->prev = deleteBlock->prev;
			}

			deleteBlock->prev->size = mergeSize;

			mergeBlock = deleteBlock->prev;
		}
	}

	if (mergeBlock->next != NULL)
	{
		if (mergeBlock->next->status == FREE)
		{
			if (mergeBlock->next == curPtr)
			{
				curPtr = mergeBlock;
			}

			mergeBlock->status = FREE;
			size_t mergeSize = 0;
			if (mergeBlock->next->next != NULL)
			{
				mergeSize = (char*)mergeBlock->next->next - (char*)(mergeBlock + 1);
			}
			else
			{
				mergeSize = (char*)(head + 1) + blockSize - (char*)(mergeBlock + 1);
			}

			
			if (mergeBlock->next->next != NULL)
			{
				mergeBlock->next->next->prev = mergeBlock;
			}
			mergeBlock->next = mergeBlock->next->next;

			mergeBlock->size = mergeSize;
		}
	}

	if (mergeBlock->next != NULL)
	{
		if ((void*)((char*)(mergeBlock + 1) + mergeBlock->size) != mergeBlock->next)
		{
			void* unallocMemPtr = (void*)((char*)(mergeBlock + 1) + mergeBlock->size);
			size_t unallocMemSize = (char*)mergeBlock->next - (char*)unallocMemPtr;

			mergeBlock->size += unallocMemSize;
		}
	}
	else
	{
		if ((void*)((char*)head + blockSize) != (void*)((char*)(mergeBlock + 1) + mergeBlock->size))
		{
			void* unallocMemPtr = (void*)((char*)(mergeBlock + 1) + mergeBlock->size);
			size_t unallocMemSize = (char*)head + blockSize - (char*)unallocMemPtr;

			mergeBlock->size += unallocMemSize;
		}
	}
}

int memgetminimumsize()
{
	return sizeof(struct List);
}

int memgetblocksize()
{
	return sizeof(struct List);
}

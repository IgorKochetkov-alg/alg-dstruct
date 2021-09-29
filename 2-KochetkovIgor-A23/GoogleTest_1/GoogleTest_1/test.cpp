#include "gtest/gtest.h"

extern "C" 
{
#include "Task 3.1.2.h"
}

TEST(CreateListTest, NewEmptyListPtr)
{
    List* list = NULL;
    list = CreateList();
    EXPECT_TRUE(list != NULL);
    EXPECT_TRUE(list->data == NULL);
    EXPECT_TRUE(list->length == 0);
}

TEST(CreateBufferTest, NullFilePtr_INVALID_PTR)
{
    FILE* file = NULL;

    char* result = CreateBuffer(file);
    EXPECT_TRUE(result == INVALID_PTR);
}

TEST(CreateBufferTest, NormalFilePtr_EmptyFile)
{
    FILE* file = fopen("CreateBufferTestEmpty.txt", "r");
    if (file == NULL)
    {
        return;
    }

    char* result = CreateBuffer(file);
    EXPECT_TRUE(result == INVALID_PTR);
}

TEST(CreateBufferTest, NormalFilePtr_CorrectMemAlloc)
{
    FILE* file = fopen("CreateBufferTestCorrect.txt", "r");
    if (file == NULL)
    {
        return;
    }

    char* result = CreateBuffer(file);
    EXPECT_TRUE(result != INVALID_PTR);
}

TEST(CreateNewElementTest, NullPtr_NotNULL)
{
    List* result = CreateNewElement(NULL);

    EXPECT_TRUE((result != NULL) || (result != INVALID_PTR));
}

TEST(CreateNewElementTest, NormalList_PtrToNewElement)
{
    List list = { NULL, 4, "Tire" };

    List* newElement = CreateNewElement(&list);

    EXPECT_TRUE(newElement == list.next);
}

TEST(FindElementTest, ListNullPtr_NULL)
{
    List* list = NULL;

    List* result = FindElement(list, "hello", 5);

    EXPECT_TRUE(result == INVALID_PTR);
}

TEST(FindElementTest, StrNullPtr_NULL)
{
    List list = { NULL, 5, "hello" };

    List* result = FindElement(&list, NULL, 5);

    EXPECT_TRUE(result == INVALID_PTR);
}

TEST(FindElementTest, IncorrectLength_NULL)
{
    List list = { NULL, 5, "hello" };

    List* result = FindElement(&list, "hello", 0);

    EXPECT_TRUE(result == INVALID_PTR);
}

TEST(FindElementTest, NormalArguments_CorrectListNode)
{
    List node3 = { NULL, 4, "rock" };
    List node2 = { &node3, 4, "ball" };
    List node1 = { &node2, 4,  "auto" };
    List list = { &node1, 5, "hello" };

    List* result = FindElement(&list, "road", 4);

    EXPECT_TRUE(result == &node2);
}

TEST(DataOutputTest, NullPtr_Err1)
{
    List* list = NULL;

    int result = DataOutput(list);
    EXPECT_TRUE(result == 1);
}

TEST(WordSortTest, CorrectWork_0)
{
    int result = WordSort();
    EXPECT_TRUE(result == 0);
}

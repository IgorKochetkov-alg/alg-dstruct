#include "gtest/gtest.h"

extern "C"
{
#include "func.h"
}

TEST(SystemInitTest, NullFilePtr_INVALID_PTR_CODE)
{
	FILE* file = NULL;
	int result = SystemInit(file);

	EXPECT_TRUE(result == INVALID_PTR_CODE);
}

TEST(SystemInitTest, NormalFilePtr_EmptyFile)
{
	FILE* file = fopen("EmptyFile.txt", "r");

	if (file == NULL)
	{
		return;
	}

	int result = SystemInit(file);

	EXPECT_TRUE(result == INVALID_PTR_CODE);
}

TEST(SystemInitTest, NormalFilePtr_Correct_WORK_CODE)
{
	FILE* file = fopen("NormalFile.txt", "r");

	if (file == NULL)
	{
		return;
	}

	int result = SystemInit(file);

	EXPECT_TRUE(result == CORRECT_WORK_CODE);
}

TEST(ExploreGrafTest, TwoNullFilePtr_INVALID_PTR_CODE)
{
	FILE* input = NULL;
	FILE* output = NULL;

	int result = ExploreGraf(input, output);

	EXPECT_TRUE(result == INVALID_PTR_CODE);
}

TEST(ExploreGrafTest, InputNullFilePtr_INVALID_PTR_CODE)
{
	FILE* input = NULL;
	FILE* output = fopen("output.txt", "w");

	if (output == NULL)
	{
		return;
	}

	int result = ExploreGraf(input, output);

	EXPECT_TRUE(result == INVALID_PTR_CODE);
}

TEST(ExploreGrafTest, OutputNullFilePtr_INVALID_PTR_CODE)
{
	FILE* input = fopen("input.txt", "r");
	FILE* output = NULL;

	if (input == NULL)
	{
		return;
	}

	int result = ExploreGraf(input, output);

	EXPECT_TRUE(result == INVALID_PTR_CODE);
}

TEST(ExploreGrafTest, InvalidDataInFile_INCORRECT_DATA_CODE)
{
	FILE* input = fopen("IncorrectData.txt", "r");
	FILE* output = fopen("output.txt", "w");

	if ((input == NULL) || (output == NULL))
	{
		return;
	}

	int result = ExploreGraf(input, output);

	EXPECT_TRUE(result == INVALID_DATA_CODE);
}

TEST(ExploreGrafTest, CorrectWork_CORRECT_WORK_CODE)
{
	FILE* input = fopen("NormalFile.txt", "r");
	FILE* output = fopen("output.txt", "w");

	if ((input == NULL) || (output == NULL))
	{
		return;
	}

	int result = ExploreGraf(input, output);
	int k = 2;

	EXPECT_TRUE(result != 0);
	EXPECT_LE(result, k);
}
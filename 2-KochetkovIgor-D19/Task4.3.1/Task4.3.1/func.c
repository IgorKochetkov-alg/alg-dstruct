#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func.h"

#define MAX_LENGTH 10
#define TRUE 1
#define FALSE 0

#define TEST_SIZE 9999


/*PC configuration:
	CPU:            AMD Ryzen 5 4600H 6-Core Processor 3 GHz
	RAM:            DDR4-3200MGz 8GB
	SSD:            NVMe 4x 8.0 GT/s   KINGSTON[512GB]

Test results(9999 vertex):
	Time: 33s;
	Memory: 108MB
*/


int k = 0;
int vertex = 0;

char* check = NULL;
char* result = NULL;


int SystemInit(FILE* file)
{
	if (file == NULL)
	{
		return INVALID_PTR_CODE;
	}

	fscanf(file, "%d %d\n", &vertex, &k);

	if ((vertex == 0) || (k == 0))
	{
		return INVALID_PTR_CODE;
	}

	check = (char*)calloc(vertex, sizeof(char));
	result = (char*)calloc(vertex, sizeof(char));

	if ((check == NULL) || (result == NULL))
	{
		return INVALID_PTR_CODE;
	}

	return 0;
}

int ExploreGraf(FILE* input, FILE* output)
{
	if (SystemInit(input) || (output == NULL))
	{
		return INVALID_PTR_CODE;
	}

	int vert1 = 0;
	int vert2 = 0;
	int count = 0;
	int n = 0;

	char sym = 0;
	char buf[MAX_LENGTH] = { 0 };

	while ((sym = fgetc(input)) != EOF)
	{
		switch (sym)
		{

		case '\n':
		{
			sscanf(buf, "%d %d", &vert1, &vert2);

			if ((vert1 <= 0) || (vert2 <= 0))
			{
				return INVALID_DATA_CODE;
			}

			if (vert1 == vert2)
			{
				return INVALID_DATA_CODE;
			}

			memset(buf, '\0', MAX_LENGTH);
			n = 0;
			break;
		}
		default:
		{
			buf[n] = sym;
			n++;
			break;
		}
		}

		if ((vert1 > 0) && (vert2 > 0))
		{
			if ((check[vert1] == FALSE) && (check[vert2] == FALSE))
			{
				//fprintf(stdout, "%d %d\n", vert1, vert2);

				result[count] = vert1;
				check[vert1] = TRUE;
				count++;

				result[count] = vert2;
				check[vert2] = TRUE;
				count++;
			}

			vert1 = 0;
			vert2 = 0;
		}
	}

	fclose(input);

	if (count <= k)
	{
		for (int i = 0; i < count; i++)
		{
			fprintf(output, "%d ", result[i]);
		}

		fclose(output);
		return count;
	}
	else
	{
		fclose(output);
		return 0;
	}
}

void CreateTestMatrix()
{
	srand(time(NULL));

	int k = 0;

	char** mtrx = NULL;
	mtrx = (char**)calloc(TEST_SIZE, sizeof(char*));

	if (mtrx == NULL)
	{
		return;
	}

	for (int i = 0; i < TEST_SIZE; i++)
	{
		mtrx[i] = (char*)calloc(TEST_SIZE, sizeof(char));

		if (mtrx[i] == NULL)
		{
			return;
		}
	}

	for (int i = 0; i < TEST_SIZE; i++)
	{
		for (int j = 0; j < TEST_SIZE; j++)
		{
			if (i == j)
			{
				mtrx[i][j] = 0;

			}
			else
			{
				mtrx[i][j] = rand() % 2;
			}
		}
	}

	FILE* file = fopen("Mtrx.txt", "w");

	if (file == NULL)
	{
		return;
	}

	k = rand() % (TEST_SIZE - 1) + 1;

	fprintf(file, "%d %d\n", TEST_SIZE, k);

	for (int i = 0; i < TEST_SIZE; i++)
	{
		for (int j = i; j < TEST_SIZE; j++)
		{
			if (mtrx[i][j] == 1)
			{
				fprintf(file, "%d %d\n", (i + 1), (j + 1));
			}
		}
	}

	fclose(file);
	free(mtrx);
	return;
}

void StressTest()
{
	CreateTestMatrix();

	FILE* input = fopen("Mtrx.txt", "r");
	FILE* output = fopen("output.txt", "w");

	ExploreGraf(input, output);
}


int main(void)
{
	//FILE* file = fopen("input.txt", "r");
	//ExploreGraf(file);

	StressTest();

	free(check);
	free(result);
}

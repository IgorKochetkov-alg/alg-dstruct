#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTEX_LENGTH 6
#define TEST_SIZE 15000

/*PC configuration:
    CPU:            AMD Ryzen 5 4600H 6-Core Processor 3 GHz
    RAM:            DDR4-3200MGz 8GB
    SSD:            NVMe 4x 8.0 GT/s   KINGSTON[512GB]
	
Test results(15000 vertex):
    Time: 33s;
	Memory: 229.5MB
*/

char** grafMatrix = NULL;
int* way = NULL;
char* check = NULL;
int nPoints = 0;

void FillInMatrix(FILE* flow);

int SystemInit(FILE* flow)
{
	fscanf(flow, "%d", &nPoints);

	if (nPoints == 0)
	{
		return 1;
	}

	grafMatrix = (char**)calloc(nPoints, sizeof(char*));
	way = (int*)calloc(nPoints, sizeof(int));
	check = (char*)calloc(nPoints, sizeof(char));

	if ((grafMatrix == NULL) || (way == NULL) || (check == NULL))
	{
		return 2;
	}

	way[0] = 0;
	check[0] = TRUE;

	for (int i = 0; i < nPoints; i++)
	{
		grafMatrix[i] = (char*)calloc(nPoints, sizeof(char));

		if (grafMatrix[i] == NULL)
		{
			return 2;
		}
	}

	FillInMatrix(flow);

	return 0;
}

void FillInMatrix(FILE* flow)
{
	int count = -1;
	int curVert = -1;
	int i = 0;
	char number[MAX_VERTEX_LENGTH] = { 0 };

	while (count < nPoints)
	{
		char sym = fgetc(flow);

		if ((sym == ' ') || (sym == '\n'))
		{
			if (i != 0)
			{
				number[i] = '\0';

				if (curVert == -1)
				{
					curVert = atoi(number);
				}
				else
				{
					int vertex = atoi(number);
					grafMatrix[curVert][vertex] = TRUE;
					grafMatrix[vertex][curVert] = TRUE;
				}

			}

			if (sym == '\n')
			{
				count++;
				curVert = -1;
			}
			memset(number, '\0', sizeof(number));
			i = 0;
		}
		if ((sym != ' ') && (sym != '\n'))
		{
			number[i] = sym;
			i++;
		}
	}
}

void BFSearch()
{
	int nextNum = 1;
	int oldNum = 0;

	while (nextNum < nPoints)
	{
		for (int i = 0; i < nPoints; i++)
		{
			if (grafMatrix[way[oldNum]][i] == TRUE)
			{
				if (check[i] == FALSE)
				{
					check[i] = TRUE;
					way[nextNum] = i;
					nextNum++;
				}
			}
		}
		oldNum++;
	}
}

void CreateTestMatrix()
{
	srand(time(NULL));

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
		for (int j = i; j < TEST_SIZE; j++)
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

	fprintf(file, "%d\n", TEST_SIZE);

	for (int i = 0; i < TEST_SIZE; i++)
	{
		fprintf(file, "%d ", i);

		for (int j = i; j < TEST_SIZE; j++)
		{
			if (mtrx[i][j] == 1)
			{
				fprintf(file, "%d ", j);
			}
		}

		fprintf(file, "\n");
	}

	fclose(file);

	return;
}

void StressTest()
{
	CreateTestMatrix();

	FILE* file = fopen("Mtrx.txt", "r");

	if (file == NULL)
	{
		return;
	}

	if (SystemInit(file) != 0)
	{
		return;
	}

	fclose(file);

	BFSearch();

	for (int i = 0; i < nPoints; i++)
	{
		fprintf(stdout, "%d ", way[i]);
	}

	return;
}

int main(void)
{
	if (SystemInit(stdin) != 0)
	{
		return 1;
	}

	for (int i = 0; i < nPoints; i++)
	{
		for (int j = 0; j < nPoints; j++)
		{
			fprintf(stdout, "%d ", grafMatrix[i][j]);
		}
		fprintf(stdout, "\n");
	}

	BFSearch();

	for (int i = 0; i < nPoints; i++)
	{
		fprintf(stdout, "%d ", way[i]);
	}

	//StressTest();

	return 0;
}
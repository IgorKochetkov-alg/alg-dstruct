#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "func.h"

static int u = 0, v = 0;
static int vertexNumber = TEST_VERTEX_NUMBER;
static int* cover = NULL;
static int** graph = NULL;
static int k = 0;
static int p, q;

static int flag = FALSE;
static int check;

int SystemInit()
{
	graph = (int**)calloc(vertexNumber, sizeof(int*));
	cover = (int*)calloc(vertexNumber, sizeof(int));

	if ((graph == NULL) || (cover == NULL))
	{
		return INVALID_PTR_CODE;
	}

	for (int i = 0; i < vertexNumber; i++)
	{
		graph[i] = (int*)calloc(vertexNumber, sizeof(int));

		if (graph[i] == NULL)
		{
			return INVALID_PTR_CODE;
		}
	}
	return SUCCES_PTR_CODE;
}

void ChangeCover(int* way, int length) 
{
	if (way[0] == 0) 
	{
		way[0] = 1;
		return;
	}
	else
	{
		int i = 0;
		while (way[i] == 1 && i < length) 
		{
			way[i] = 0;
			i++;
		}

		if (i < length)
		{
			way[i] = 1;
		}

		return;
	}
}

int FindVertSumInCover(int* way, int length) 
{
	int sum = 0;

	for (int i = 0; i <length; i++)
	{
		if (way[i] == 1)
		{
			sum++;
		}
	}
		
	return sum;
}

int StressTest(FILE* test_file)
{
	srand(time(NULL));

	vertexNumber = TEST_VERTEX_NUMBER;
	k = TEST_K;

	if (SystemInit() == INVALID_PTR_CODE)
	{
		return INVALID_PTR_CODE;
	}

	fprintf(test_file, "%d %d\n", vertexNumber, k);
	
	for (int i = 0; i < vertexNumber; i++)
	{
		for (int j = i; j < vertexNumber; j++)
		{
			if (i != j){
				graph[i][j] = rand() % 2;
				if ((graph[j][i] = graph[i][j])){
					fprintf(test_file, "%d %d\n", i+1, j+1);
				}
				
			}
		}
	}
	fprintf(test_file, "0 0");
	return SUCCES_PTR_CODE;
}

int solve(FILE* input, FILE* output) 
{
	flag = FALSE;
	fscanf(input, "%d %d\n", &vertexNumber, &k);

	if (SystemInit() == INVALID_PTR_CODE)
	{
		return INVALID_PTR_CODE;
	}

	while (fscanf(input, "%d %d\n", &u, &v) == 2) 
	{

		if (u == 0 || v == 0)
		{
			break;
		}

		graph[u - 1][v - 1] = TRUE;
		graph[v - 1][u - 1] = TRUE;
	}

	/*for (int i = 0; i < vertexNumber; i++)
	{
		for (int j = 0; j < vertexNumber; j++)
		{
			printf("%d ", graph[i][j]);
		}

		printf("\n");
	}*/
	
	while ((FindVertSumInCover(cover, vertexNumber) < vertexNumber) && (flag == FALSE))
	{
		ChangeCover(cover, vertexNumber);

		check = TRUE;

		if (FindVertSumInCover(cover, vertexNumber) <= k)
		{
			p = 0;
			q = 0;

			while ((p < vertexNumber) && (check == TRUE))
			{
				while ((q < vertexNumber) && (check == TRUE))
				{
					if ((graph[p][q] == TRUE) && (cover[p] == FALSE) && (cover[q] == FALSE))
					{
						check = FALSE;
					}

					q++;
				}

				q = 0;
				p++;
			}

			if (check == TRUE)
			{
				flag = TRUE;
			}
		}
	}

	if (flag == TRUE && vertexNumber > 0)
	{
		for (int i = 0; i < vertexNumber; i++)
		{
			if (cover[i] == TRUE)
			{
				fprintf(output, "%d ", i + 1);
			}
		}
	}
	else
	{
		fprintf(output, "%d", 0);
	}

	return 0;
}

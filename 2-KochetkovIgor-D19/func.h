#pragma once
#include <stdio.h>

#define INVALID_PTR_CODE 0
#define SUCCES_PTR_CODE 1
#define TRUE 1
#define FALSE 0
#define TEST_VERTEX_NUMBER 27
#define TEST_K 20

int StressTest ( FILE* test_file );
void ChangeCover(int* way, int length);
int FindVertSumInCover(int* way, int length);
int solve(FILE* input, FILE* output);

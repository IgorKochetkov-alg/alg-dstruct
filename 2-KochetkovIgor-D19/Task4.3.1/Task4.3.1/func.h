#pragma once

#include <limits.h>

#define INVALID_PTR_CODE 1
#define CORRECT_WORK_CODE 0
#define INVALID_DATA_CODE 2


int SystemInit(FILE* file);

int ExploreGraf(FILE* input, FILE* output);

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "func.h"


/*PC configuration:
	CPU:            AMD Ryzen 5 4600H 6-Core Processor 3 GHz
	RAM:            DDR4-3200MGz 8GB
	SSD:            NVMe 4x 8.0 GT/s   KINGSTON[512GB]

Test results(27 vertex; k = 20):
	Time: 47.336s;
	Memory: 7.8Kb
*/


int main() 
{
// 	FILE* test = fopen("StressTest.txt", "w");
// 	if (test == NULL)
// 		return 0;
// 	StressTest(test);
// 	freopen("StressTest.txt", "r", test);
	FILE* test = fopen("StressTest.txt", "r");
	solve(test, stdout);
	return 0;
}

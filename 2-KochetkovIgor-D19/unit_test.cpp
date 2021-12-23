#include <gtest/gtest.h>

extern "C" {
	#include "func.h"
	#include <string.h>
}

#define TEST_CHECK_LINE 100
#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

TEST(simple_test, test1) {
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "3 1\n"\
		"2 3\n"\
		"1 3\n"\
		"1 2\n");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}

TEST(simple_test, test2) {
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "3 1\n"\
		"1 3\n"\
		"1 2\n");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "1 ") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}


TEST(ChangeCover_testing, nullptr_test_zero_size){
	EXPECT_EXIT(ChangeCover(nullptr, 0),::testing::KilledBySignal(SIGSEGV),".*");
}

TEST(ChangeCover_testing, nullptr_test_non_zero_size){
	EXPECT_EXIT(ChangeCover(nullptr, 1),::testing::KilledBySignal(SIGSEGV),".*");
}

TEST(ChangeCover_testing, test_one_zero_el){
	int val[1] = {0};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 1));
	EXPECT_EQ(*val, 1);
}

TEST(ChangeCover_testing, test_one_nonzero_el){
	int val[1] = {1};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 1));
	EXPECT_EQ(*val, 0);
}

TEST(ChangeCover_testing, test_two_zero_el){
	int val[2] = {0};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 2));
	EXPECT_EQ(val[0], 1);
	EXPECT_EQ(val[1], 0);
}

TEST(ChangeCover_testing, test_two_nonzero_el){
	int val[2] = {1, 1};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 2));
	EXPECT_EQ(val[0], 0);
	EXPECT_EQ(val[1], 0);
}

TEST(ChangeCover_testing, test_two_zero_and_nonzero_el_case1){
	int val[2] = {1, 0};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 2));
	EXPECT_EQ(val[0], 0);
	EXPECT_EQ(val[1], 1);
}

TEST(ChangeCover_testing, test_two_zero_and_nonzero_el_case2){
	int val[2] = {0, 1};
	EXPECT_NO_FATAL_FAILURE(ChangeCover(val, 2));
	EXPECT_EQ(val[0], 1);
	EXPECT_EQ(val[1], 1);
}

TEST(FindVertSumInCover_testing, test_nullptr_zero_size){
	EXPECT_NO_FATAL_FAILURE(FindVertSumInCover(nullptr, 0));
	EXPECT_EQ(FindVertSumInCover(nullptr, 0), 0);
}

TEST(FindVertSumInCover_testing, test_one_size_with_zero){
	int val[] = {0};
	EXPECT_EQ(FindVertSumInCover(val, 1), 0);
}

TEST(FindVertSumInCover_testing, test_one_size_with_one){
	int val[] = {1};
	EXPECT_EQ(FindVertSumInCover(val, 1), 1);
}

TEST(Solving_testing, test_zero_args){
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "0 1\n");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}

TEST(Solving_testing, test_one_arg){
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "1 1\n");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "1 ") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}

TEST(Solving_testing, test_two_arg_with_link_and_one_k){
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "2 1\n"\
		"1 2");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "1 ") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}

TEST(Solving_testing, test_two_arg_with_link_and_two_in_k){
	FILE* Fp_i = fopen(INPUT_FILENAME, "w");

	fprintf(Fp_i, "2 2\n"\
		"1 2");

	freopen(INPUT_FILENAME, "r", Fp_i );
	FILE* Fp_o = fopen(OUTPUT_FILENAME, "w");

	solve(Fp_i, Fp_o);
	
	freopen(OUTPUT_FILENAME, "r", Fp_o);
	
	char line[TEST_CHECK_LINE] = {0};
	fgets(line, TEST_CHECK_LINE, Fp_o);
	
	EXPECT_TRUE(strcmp(line, "1 ") == 0);
	
	fclose(Fp_i);
	fclose(Fp_o);
	remove(INPUT_FILENAME);
	remove(OUTPUT_FILENAME);
}


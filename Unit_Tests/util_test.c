#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../color.h"
#include "../util.h"
#include "minunit.h"

static char * test_substring(void);
static char * test_str_split(void);
static char * test_multi_str_split(void);
static char * test_count_delimiter(void);

int tests_run = 0;

#define STRING "TEST STRING"
#define LONG_STRING "TEST LONG STRING"

#define EXPECTED_COUNT "2"
#define EXPECTED0 "TEST"
#define EXPECTED1 "STRING"
#define EXPECTED2 "LONG"

#define MSG_test_substring_0 "Error, test_substring s1 should be "EXPECTED0
#define MSG_test_substring_1 "Error, test_substring s2 should be "EXPECTED1

#define MSG_test_str_split_0 "Error, test_str_split arr[0] should be "EXPECTED0
#define MSG_test_str_split_1 "Error, test_str_split arr[1] should be "EXPECTED1

#define MSG_test_multi_str_split_0 "Error, test_multi_str_split arr[0] should be "EXPECTED0
#define MSG_test_multi_str_split_1 "Error, test_multi_str_split arr[1] should be "EXPECTED2
#define MSG_test_multi_str_split_2 "Error, test_multi_str_split arr[2] should be "EXPECTED1

#define MSG_test_count_delimiter "Error, test_count_delimiter del_count should be "EXPECTED_COUNT

static char * test_substring() 
{
    char * s1 = substring(0, 4, STRING);
    char * s2 = substring(5, 0, STRING);
	
	printf("Extracted: %s from "STRING"\nExtracted: %s from "STRING"\n", s1, s2);
    mu_assert(MSG_test_substring_0, strcmp(s1,EXPECTED0) == 0);
    mu_assert(MSG_test_substring_1, strcmp(s2,EXPECTED1) == 0);
    free(s1); free(s2);

	printf("\ntest_substring ");
	print_color(GREEN, "PASSED\n\n");
    
    return 0;
}

static char * test_str_split()
{
    char ** arr = str_split(STRING, ' ');

	printf("arr[0] is %s from "STRING"\narr[1] is %s from "STRING"\n", arr[0], arr[1]);
    mu_assert(MSG_test_str_split_0, strcmp(arr[0],EXPECTED0) == 0);
    mu_assert(MSG_test_str_split_1, strcmp(arr[1],EXPECTED1) == 0);
    free(arr);

	printf("\ntest_str_split ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char * test_multi_str_split()
{
    char ** arr = multi_str_split(LONG_STRING, ' ');

    printf("arr[0] is %s\narr[1] is %s\narr[2] is %s\nFrom: "LONG_STRING"\n", arr[0], arr[1], arr[2]);
    mu_assert(MSG_test_multi_str_split_0, strcmp(arr[0],EXPECTED0) == 0);
    mu_assert(MSG_test_multi_str_split_1, strcmp(arr[1],EXPECTED2) == 0);
    mu_assert(MSG_test_multi_str_split_2, strcmp(arr[2],EXPECTED1) == 0);
    free(arr);

    printf("\ntest_multi_str_split ");
    print_color(GREEN, "PASSED\n");

    return 0;
}

static char * test_count_delimiter()
{
    int del_count = count_delimiter(LONG_STRING, ' ');

    printf("del_count is %d from "LONG_STRING"\n", del_count);
    mu_assert(MSG_test_count_delimiter, del_count == atoi(EXPECTED_COUNT));

    printf("\ntest_count_delimiter ");
    print_color(GREEN, "PASSED\n\n");

    return 0;
}


static char* all_tests() 
{
    mu_run_test(test_substring);
    mu_run_test(test_str_split);
    mu_run_test(test_count_delimiter);
    mu_run_test(test_multi_str_split);
    return 0;
}

int main(int argc, const char* argv[])
{
    char *result = all_tests();
    if (result != 0) {
		printf("\n");
		print_color(RED, result);
		printf("\n");
    }
    else {
		printf("\n#####################\n");
        print_color(GREEN,"ALL UTIL TESTS PASSED\n");
		printf("#####################\n");
    }
    printf("\nTests run: %d\n", tests_run);

    return result != 0;
}
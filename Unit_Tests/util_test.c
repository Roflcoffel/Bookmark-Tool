#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../color.h"
#include "../util.h"
#include "minunit.h"

static char * test_substring(void);
static char * test_str_split(void);

int tests_run = 0;

#define SIZE 255

#define STRING "TEST STRING"

#define EXPECTED0 "TEST"
#define EXPECTED1 "STRING"

#define MSG_test_substring_0 "Error, test_substring s1 should be "EXPECTED0
#define MSG_test_substring_1 "Error, test_substring s2 should be "EXPECTED1

#define MSG_test_str_split_0 "Error, test_str_split arr[0] should be "EXPECTED0
#define MSG_test_str_split_1 "Error, test_str_split arr[1] should be "EXPECTED1

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

	printf("a[0] is %s from "STRING"\na[1] is %s from "STRING"\n", arr[0], arr[1]);
    mu_assert(MSG_test_str_split_0, strcmp(arr[0],EXPECTED0) == 0);
    mu_assert(MSG_test_str_split_1, strcmp(arr[1],EXPECTED1) == 0);
    free(arr);

	printf("\ntest_str_split ");
	print_color(GREEN, "PASSED\n");

    return 0;
}

static char* all_tests() 
{
    mu_run_test(test_substring);
    mu_run_test(test_str_split);
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
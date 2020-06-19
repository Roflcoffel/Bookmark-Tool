#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../size.h"
#include "../color.h"
#include "../util.h"
#include "minunit.h"

static char * test_substring(void);
static char * test_str_split(void);
static char * test_multi_str_split(void);
static char * test_count_delimiter(void);
static char * test_char_replace(void);

int tests_run = 0;

#define STRING "TEST STRING"
#define LONG_STRING "TEST LONG STRING"
#define NO_SPACE "NO_SPACE"
#define PATH "/mnt/windows/Random/Place/Wow"

#define P_EXPECTED_SIZE "5"
#define P_EXPECTED0 "mnt"
#define P_EXPECTED1 "windows"
#define P_EXPECTED2 "Random"
#define P_EXPECTED3 "Place"
#define P_EXPECTED4 "Wow"

#define EXPECTED_COUNT "2"
#define EXPECTED0 "TEST"
#define EXPECTED1 "STRING"
#define EXPECTED2 "LONG"
#define EXPECTED_SIZE "3"

#define EXPECTED_LONG_STRING "TEST_LONG_STRING"

#define MSG_test_substring_0 "Error, test_substring s1 should be "EXPECTED0
#define MSG_test_substring_1 "Error, test_substring s2 should be "EXPECTED1

#define MSG_test_str_split_0 "Error, test_str_split arr[0] should be "EXPECTED0
#define MSG_test_str_split_1 "Error, test_str_split arr[1] should be "EXPECTED1

#define MSG_test_str_split_no_delimiter "Error, test_str_split no_space[0] should be "NO_SPACE

#define MSG_test_multi_str_split_0 "Error, test_multi_str_split arr[0] should be "EXPECTED0
#define MSG_test_multi_str_split_1 "Error, test_multi_str_split arr[1] should be "EXPECTED2
#define MSG_test_multi_str_split_2 "Error, test_multi_str_split arr[2] should be "EXPECTED1
#define MSG_test_multi_str_split_size "Error, test_multi_str_split size should be "EXPECTED_SIZE

#define MSG_test_multi_str_split_path_0 "Error, test_multi_str_split arr[0] should be "P_EXPECTED0
#define MSG_test_multi_str_split_path_1 "Error, test_multi_str_split arr[1] should be "P_EXPECTED1
#define MSG_test_multi_str_split_path_2 "Error, test_multi_str_split arr[2] should be "P_EXPECTED2
#define MSG_test_multi_str_split_path_3 "Error, test_multi_str_split arr[3] should be "P_EXPECTED3
#define MSG_test_multi_str_split_path_4 "Error, test_multi_str_split arr[4] should be "P_EXPECTED4
#define MSG_test_multi_str_split_path_size "Error, test_multi_str_split size should be "P_EXPECTED_SIZE

#define MSG_test_multi_str_split_no_space "Error, test_multi_str_split no_space[0] should be "NO_SPACE

#define MSG_test_count_delimiter "Error, test_count_delimiter del_count should be "EXPECTED_COUNT

#define MSG_test_char_replace "Error, test_char_replace string should be "EXPECTED_LONG_STRING

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

    char ** no_space = str_split(NO_SPACE, ' ');
    printf("no_space[0] is %s from "NO_SPACE"\n", no_space[0]);
    mu_assert(MSG_test_str_split_no_delimiter, strcmp(no_space[0], NO_SPACE) == 0);
    free(no_space);

	printf("\ntest_str_split ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char * test_multi_str_split()
{
    size_t size_arr = 0;
    char ** arr = multi_str_split(LONG_STRING, ' ', &size_arr);

    printf("size is %d\narr[0] is %s\narr[1] is %s\narr[2] is %s\nFrom: "LONG_STRING"\n", size_arr, arr[0], arr[1], arr[2]);
    mu_assert(MSG_test_multi_str_split_size, size_arr == atoi(EXPECTED_SIZE));
    mu_assert(MSG_test_multi_str_split_0, strcmp(arr[0],EXPECTED0) == 0);
    mu_assert(MSG_test_multi_str_split_1, strcmp(arr[1],EXPECTED2) == 0);
    mu_assert(MSG_test_multi_str_split_2, strcmp(arr[2],EXPECTED1) == 0);
    free(arr);

    size_t size_path_arr = 0;
    char ** path_arr = multi_str_split(PATH, '/', &size_path_arr);

    printf("\nsize is %d\narr[0] is %s\narr[1] is %s\narr[2] is %s\narr[3] is %s\narr[4] is %s\nFrom: "PATH"\n",
        size_path_arr, path_arr[0], path_arr[1], path_arr[2], path_arr[3], path_arr[4]
    );

    mu_assert(MSG_test_multi_str_split_path_size, size_path_arr == atoi(P_EXPECTED_SIZE));
    mu_assert(MSG_test_multi_str_split_path_0, strcmp(path_arr[0],P_EXPECTED0) == 0);
    mu_assert(MSG_test_multi_str_split_path_1, strcmp(path_arr[1],P_EXPECTED1) == 0);
    mu_assert(MSG_test_multi_str_split_path_2, strcmp(path_arr[2],P_EXPECTED2) == 0);
    mu_assert(MSG_test_multi_str_split_path_3, strcmp(path_arr[3],P_EXPECTED3) == 0);
    mu_assert(MSG_test_multi_str_split_path_4, strcmp(path_arr[4],P_EXPECTED4) == 0);
    free(path_arr);

    size_t size_no_space = 0;
    char ** no_space = multi_str_split(NO_SPACE, ' ', &size_no_space);
    printf("\nsize is %d\nno_space[0] is %s\nFrom: "NO_SPACE"\n", size_no_space, no_space[0]);
    mu_assert(MSG_test_multi_str_split_no_space, strcmp(no_space[0],NO_SPACE) == 0);
    free(no_space);

    printf("\ntest_multi_str_split ");
    print_color(GREEN, "PASSED\n\n");

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

static char * test_char_replace()
{
    char str[] = LONG_STRING;
    char_replace(str, ' ', '_');

    printf("string is %s from "LONG_STRING"\n", str);
    mu_assert(MSG_test_char_replace, strcmp(EXPECTED_LONG_STRING, str) == 0);

    printf("\ntest_char_replace ");
    print_color(GREEN, "PASSED\n");

    return 0;
}

static char* all_tests() 
{
    mu_run_test(test_substring);
    mu_run_test(test_str_split);
    mu_run_test(test_count_delimiter);
    mu_run_test(test_multi_str_split);
    mu_run_test(test_char_replace);
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
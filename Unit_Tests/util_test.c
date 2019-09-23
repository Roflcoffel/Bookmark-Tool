#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util.h"
#include "minunit.h"

static char * test_substring(void);
static char * test_str_split(void);

int tests_run = 0;

#define SIZE 255

#define STRING "TEST STRING"

#define EXPECTED0 "TEST"
#define EXPECTED1 "STRING"

#define MSG_test_substring_0 "Error, test_substring s1 != "EXPECTED0
#define MSG_test_substring_1 "Error, test_substring s1 != "EXPECTED1

#define MSG_test_str_split_0 "Error, test_str_split arr[0] != "EXPECTED0
#define MSG_test_str_split_1 "Error, test_str_split arr[1] != "EXPECTED1

static char * test_substring() 
{
    char buffer_s1[SIZE];
    char * s1 = substring(0, 4, STRING);
    snprintf(buffer_s1, sizeof(s1), "%s \nValue was: %s", MSG_test_str_split_0, s1);
    mu_assert(buffer_s1, strcmp(s1,EXPECTED0) == 0);

    char buffer_s2[SIZE];
    char * s2 = substring(5, 0, STRING);
    snprintf(buffer_s2, sizeof(s2), "%s \nValue was: %s", MSG_test_str_split_1, s2);
    mu_assert(buffer_s2, strcmp(s2,EXPECTED1) == 0);

    free(s1); free(s2);
    return 0;
}

static char * test_str_split()
{
    char ** arr = str_split(STRING, ' ');

    char buffer_arr_0[SIZE];
    snprintf(buffer_arr_0, sizeof(arr[0]), "%s \nValue was: %s", MSG_test_str_split_0, arr[0]);

    char buffer_arr_1[SIZE];
    snprintf(buffer_arr_1, sizeof(arr[1]), "%s \nValue was: %s", MSG_test_str_split_1, arr[1]);

    mu_assert(buffer_arr_0, strcmp(arr[0],EXPECTED0) == 0);
    mu_assert(buffer_arr_1, strcmp(arr[1],EXPECTED1) == 0);

    free(arr);

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
        printf("%s\n", result);
    }
    else {
        printf("ALL VECTOR TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
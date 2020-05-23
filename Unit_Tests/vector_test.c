#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../color.h"
#include "../vector.h"
#include "minunit.h"

static char*  test_dict_new(void);
static char*  test_vector_new(void);

static char*  test_vector_add(void);
static char*  test_vector_find(void);
static char*  test_vector_match(void);
static char*  test_vector_find_index(void);
static char*  test_vector_remove(void);
static char*  test_vector_destroy(void); //do not know how to test, maybe try to use the object after?

static char*  all_tests(void);
static Vector Setup(void);

int tests_run = 0;

#define VALUE 5
#define INDEX 2
#define STRING "TEST"

#define DATA "DATA"
#define TDATA1 "DAT_TEST1"
#define TDATA2 "DAT_TEST2"
#define TDATA3 "DAT_TEST3"
#define TDATA4 "TEST4"

#define MSG_VALUE "5"
#define MSG_INDEX "2"

#define MSG_dict_new_key   "Error dict_new, .key should be "STRING
#define MSG_dict_new_value "Error dict_new, .value should be "MSG_VALUE

#define MSG_vector_new_size     "Error vector_new, .size should be 0"
#define MSG_vector_new_capacity "Error vector_new, .capacity should be 2"

#define MSG_vector_add_key   "Error vector_add, .key should be "STRING
#define MSG_vector_add_value "Error vector_add, .value should be "MSG_VALUE
#define MSG_vector_add_size  "Error vector_add, .size should be 1" 

#define MSG_vector_find      "Error vector_find, .key should be "STRING
#define MSG_vector_find_null "Error vector_find, .key should be NULL"

#define MSG_vector_match_string "Error vector_match, .key should be "STRING
#define MSG_vector_match_string_size "Error vector_match, .size should be 1"

#define MSG_vector_match_tdata  "Error vector_match, .data should be "TDATA1", "TDATA2", "TDATA3

#define MSG_vector_find_index      "Error vector_find_index, should be "MSG_INDEX
#define MSG_vector_find_index_fail "Error vector_find_index, should be -1"

#define MSG_vector_remove "Error vector_remove, .data[0] should be NULL"

#define SIZE 255
//////////////////////////////////////////////
static char* test_dict_new() 
{
    Dict test_dict = dict_new(STRING, VALUE);

	printf("key is %s\nvalue is %d\n", test_dict.key, test_dict.value);
	mu_assert(MSG_dict_new_key, strcmp(test_dict.key, STRING) == 0);
    mu_assert(MSG_dict_new_value, test_dict.value == VALUE);

	printf("\ntest_dict_new ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

//Currently not testing .data should equal sizeof(Dict)*capacity
static char* test_vector_new() 
{
    Vector test_vect = vector_new();

	printf("size is %d\ncapacity is %d\n", test_vect.size, test_vect.capacity);
    mu_assert(MSG_vector_new_size, test_vect.size == 0);
    mu_assert(MSG_vector_new_capacity, test_vect.capacity == 2);
    vector_destroy(&test_vect);

	printf("\ntest_vector_new ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_add() 
{
    Vector test_vect = vector_new();
    Dict test_dict = dict_new(STRING, VALUE);
    vector_add(test_dict, &test_vect);
    
	printf("key is %s\nvalue is %d\nsize is %d\n", test_vect.data[0].key, test_vect.data[0].value, test_vect.size);
    mu_assert(MSG_vector_add_key, strcmp(test_vect.data[0].key,STRING) == 0);
    mu_assert(MSG_vector_add_value, test_vect.data[0].value == VALUE);
    mu_assert(MSG_vector_add_size, test_vect.size == 1);
    vector_destroy(&test_vect);

	printf("\ntest_vector_add ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_find() 
{
    Vector test_vect = Setup();
    
    Dict found_dict = vector_find(STRING, test_vect);
    Dict null_dict = vector_find("NONE", test_vect);

	printf("found_dict.key is %s\nnull_dict.key is %s\n", found_dict.key, null_dict.key);
    mu_assert(MSG_vector_find, strcmp(found_dict.key, STRING) == 0);
    mu_assert(MSG_vector_find_null, strcmp(null_dict.key, "NULL") == 0);
    vector_destroy(&test_vect);

	printf("\ntest_vector_find ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_match() 
{
    Vector test_vect = Setup();

    Vector string_vect = vector_match(STRING, test_vect);

	printf("key is %s\nsize is %d\n\n", string_vect.data[0].key, string_vect.size);
    mu_assert(MSG_vector_match_string, strcmp(string_vect.data[0].key, STRING) == 0);
	mu_assert(MSG_vector_match_string_size, string_vect.size == 1);

    Vector data_vect = vector_match(DATA, test_vect);
    
	printf("size is %d\ndata[0].key is %s\ndata[1].key is %s\ndata[2].key is %s\n", data_vect.size, data_vect.data[0].key, data_vect.data[1].key, data_vect.data[2].key);
	mu_assert(MSG_vector_match_tdata, data_vect.size == 3);
	mu_assert(MSG_vector_match_tdata, strcmp(data_vect.data[0].key, TDATA1) == 0);
    mu_assert(MSG_vector_match_tdata, strcmp(data_vect.data[1].key, TDATA2) == 0);
    mu_assert(MSG_vector_match_tdata, strcmp(data_vect.data[2].key, TDATA3) == 0);

	vector_destroy(&string_vect);
	vector_destroy(&data_vect);
	vector_destroy(&test_vect);

	printf("\ntest_vector_match ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_find_index() 
{
    Vector test_vect = Setup();

    int test_index = vector_find_index(TDATA2, test_vect);
    int test_not_found = vector_find_index("FAIL", test_vect);

	printf("index is %d\nnot_found is %d\n", test_index, test_not_found);
    mu_assert(MSG_vector_find_index, test_index == INDEX);
    mu_assert(MSG_vector_find_index_fail, test_not_found == -1);
    vector_destroy(&test_vect);

	printf("\ntest_vector_find_index ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_remove() 
{
    Vector test_vect = Setup();
    vector_remove(STRING, &test_vect);

	printf("key is %s\n", test_vect.data[0].key);
    mu_assert(MSG_vector_remove, strcmp(test_vect.data[0].key,"NULL") == 0);
    vector_destroy(&test_vect);

	printf("\ntest_vector_remove ");
	print_color(GREEN, "PASSED\n");

    return 0;
}

///////////////////////////////////////////////
static Vector Setup() 
{
    Vector test_vect = vector_new();

    vector_add(dict_new(STRING, VALUE), &test_vect);
    vector_add(dict_new(TDATA1, VALUE), &test_vect);
    vector_add(dict_new(TDATA2, VALUE), &test_vect);
    vector_add(dict_new(TDATA3, VALUE), &test_vect);
    vector_add(dict_new(TDATA4, VALUE), &test_vect);

    return test_vect;
}

static char* all_tests() 
{
    mu_run_test(test_dict_new);
    mu_run_test(test_vector_new);
    mu_run_test(test_vector_add);
    mu_run_test(test_vector_find);
    mu_run_test(test_vector_match);
    mu_run_test(test_vector_find_index);
    mu_run_test(test_vector_remove);
    mu_run_test(test_vector_remove);
    mu_run_test(test_vector_remove);
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
		printf("\n#######################\n");
        print_color(GREEN, "ALL VECTOR TESTS PASSED\n");
		printf("#######################\n\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
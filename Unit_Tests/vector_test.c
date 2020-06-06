#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <assert.h>
#include <stdbool.h>

#include "../size.h"
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
#define MSG_VALUE "5"

#define INDEX 2
#define MSG_INDEX "2"

#define STRING "TEST"

#define MATCH_MISSPELLED "infonete"
#define MATCH_INFINITE   "infinite"
#define MATCH_NANOHA     "Nanoha"
#define MATCH_KON        "k-on!"
#define NO_MATCH         "No Match Found"

#define SERIE_0 "Infinite Dendrogram"
#define SERIE_1 "Infinite Stratos"
#define SERIE_2 "Mahou Shoujo Lyrical Nanoha"
#define SERIE_3 "K-ON!"

#define EXPECTED_INDEX_KON 4
#define EXPECTED_INDEX_KON_MSG "4"

#define EXPECTED_INDEX_NONE -1
#define EXPECTED_INDEX_NONE_MSG "-1" 

#define MSG_dict_new_key   "Error dict_new, .key should be "STRING
#define MSG_dict_new_value "Error dict_new, .value should be "MSG_VALUE

#define MSG_vector_new_size     "Error vector_new, .size should be 0"
#define MSG_vector_new_capacity "Error vector_new, .capacity should be 2"

#define MSG_vector_add_key   "Error vector_add, .key should be "STRING
#define MSG_vector_add_value "Error vector_add, .value should be "MSG_VALUE
#define MSG_vector_add_size  "Error vector_add, .size should be 1" 

#define MSG_vector_find      "Error vector_find, .key should be "MATCH_KON
#define MSG_vector_find_kon  "Error vector_find, index should be "EXPECTED_INDEX_KON_MSG

#define MSG_vector_find_null "Error vector_find, .key should be NULL"
#define MSG_vector_find_none "Error vector_find, index shoulb be "EXPECTED_INDEX_NONE_MSG

#define MSG_vector_match_string      "Error vector_match, .key should be "MATCH_NANOHA
#define MSG_vector_match_string_size "Error vector_match, .size should be 1"

#define MSG_vector_match_tdata      "Error vector_match, .data should be "SERIE_0", "SERIE_1
#define MSG_vector_match_misspelled "Error vector_match, .data should be "SERIE_0", "SERIE_1

#define MSG_vector_match_not_found "Error vector_match, .key should be "NO_MATCH

#define MSG_vector_find_index      "Error vector_find_index, should be "MSG_INDEX
#define MSG_vector_find_index_fail "Error vector_find_index, should be -1"

#define MSG_vector_remove "Error vector_remove, .data[0] should be NULL"
//////////////////////////////////////////////
static char* test_dict_new() 
{
    Dict test_dict = dict_new(STRING, VALUE);
    printf("CALL dict_new(%s, %d)\n\n", STRING, VALUE);

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
    printf("CALL vector_new()\n\n");

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
    printf("CALL vector_add( dict_new(%s, %d), %s)\n\n", STRING, VALUE, "&test_vect");
    
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
    
    int index_kon;
    int index_none;

    Dict found_dict = vector_find(MATCH_KON, test_vect, &index_kon);
    Dict null_dict = vector_find("NONE", test_vect, &index_none);
    printf("CALL vector_find(%s, %s)\n", MATCH_KON, "test_vect");
    printf("CALL vector_find(%s, %s)\n\n", "NONE", "test_vect");

	printf("found_dict.key is %s\nnull_dict.key is %s\n", found_dict.key, null_dict.key);
    mu_assert(MSG_vector_find, strcasecmp(found_dict.key, MATCH_KON) == 0);
    mu_assert(MSG_vector_find_kon, index_kon == EXPECTED_INDEX_KON);
    mu_assert(MSG_vector_find_null, strcmp(null_dict.key, "NULL") == 0);
    mu_assert(MSG_vector_find_none, index_none == EXPECTED_INDEX_NONE);
    vector_destroy(&test_vect);

	printf("\ntest_vector_find ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_match() 
{
    Vector test_vect = Setup();

    //Test one full match
    Vector string_vect = vector_match(MATCH_NANOHA, test_vect);
    printf("CALL vector_match(%s, %s)\n\n", MATCH_NANOHA, "test_vect");

	printf("key is %s\nsize is %d\n\n", string_vect.data[0].key, string_vect.size);
    mu_assert(MSG_vector_match_string, strcmp(string_vect.data[0].key, SERIE_2) == 0);
	mu_assert(MSG_vector_match_string_size, string_vect.size == 1);

    //Test multiple full matches
    Vector data_vect = vector_match(MATCH_INFINITE, test_vect);
    printf("CALL vector_match(%s, %s)\n\n", MATCH_INFINITE, "test_vect");
    
	printf("data[0].key is %s\ndata[1].key is %s\nsize is %d\n\n", data_vect.data[0].key, data_vect.data[1].key, data_vect.size);
	mu_assert(MSG_vector_match_tdata, data_vect.size == 2);
	mu_assert(MSG_vector_match_tdata, strcmp(data_vect.data[0].key, SERIE_0) == 0);
    mu_assert(MSG_vector_match_tdata, strcmp(data_vect.data[1].key, SERIE_1) == 0);

    //Test misspelled match, matches atleast 2
    Vector misspelled_vect = vector_match(MATCH_MISSPELLED, test_vect);
    printf("CALL vector_match(%s, %s)\n\n", MATCH_MISSPELLED, "test_vect");

    printf("data[0].key is %s\ndata[1].key is %s\nsize is %d\n\n", misspelled_vect.data[0].key, misspelled_vect.data[1].key, misspelled_vect.size);
    mu_assert(MSG_vector_match_misspelled, strcmp(misspelled_vect.data[0].key, SERIE_0) == 0);
    mu_assert(MSG_vector_match_misspelled, strcmp(misspelled_vect.data[1].key, SERIE_1) == 0);

    //Test no matches
    Vector no_vect = vector_match(NO_MATCH, test_vect);
    printf("CALL vector_match(%s, %s)\n\n", NO_MATCH, "test_vect");

    printf("key is %s\nsize is %d\n\n", no_vect.data[0].key, no_vect.size);
    mu_assert(MSG_vector_match_not_found, strcmp(no_vect.data[0].key, NO_MATCH) == 0);

	vector_destroy(&string_vect);
	vector_destroy(&data_vect);
	vector_destroy(&test_vect);
    vector_destroy(&no_vect);

	printf("\ntest_vector_match ");
	print_color(GREEN, "PASSED\n\n");

    return 0;
}

static char* test_vector_find_index() 
{
    Vector test_vect = Setup();

    int test_index = vector_find_index(SERIE_1, test_vect);
    int test_not_found = vector_find_index("FAIL", test_vect);
    printf("CALL vector_find_index(%s, %s)\n", SERIE_1, "test_vect");
    printf("CALL vector_find_index(%s, %s)\n\n", "FAIL", "test_vect");

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
    int index = vector_find_index(STRING, test_vect);
    vector_remove(index, &test_vect);
    printf("CALL vector_remove(%s, %s)\n\n", STRING, "&test_vect");

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
    vector_add(dict_new(SERIE_0, VALUE), &test_vect);
    vector_add(dict_new(SERIE_1, VALUE), &test_vect);
    vector_add(dict_new(SERIE_2, VALUE), &test_vect);
    vector_add(dict_new(SERIE_3, VALUE), &test_vect);

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
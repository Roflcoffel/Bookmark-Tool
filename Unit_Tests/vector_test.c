#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../vector.h"
#include "minunit.h"

static char*  test_type_new_s(void);
static char*  test_type_new_i(void);

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

#define TDATA1 "DATA"
#define TDATA2 "ATAD"
#define TDATA3 "TADA"
#define TDATA4 "ADAT"

#define MSG_VALUE "5"
#define MSG_INDEX "2"

#define MSG_type_new_s "Error type_new_s, .STR != "STRING
#define MSG_type_new_i "Error type_new_i, .INT != "MSG_VALUE

#define MSG_dict_new_key   "Error dict_new, .key != "STRING
#define MSG_dict_new_value "Error dict_new, .value.INT != "MSG_VALUE

#define MSG_vector_new_size     "Error vector_new, .size != 0"
#define MSG_vector_new_capacity "Error vector_new, .capacity != 2"

#define MSG_vector_add_key   "Error vector_add, .key != "STRING
#define MSG_vector_add_value "Error vector_add, .value != "MSG_VALUE
#define MSG_vector_add_size  "Error vector_add, .size != 1" 

#define MSG_vector_find      "Error vector_find, .key != "STRING
#define MSG_vector_find_null "Error vector_find, .key != NULL"

#define MSG_vector_match_string "Error vector_match, .key != "STRING
#define MSG_vector_match_tdata  "Error vector_match, .key != "TDATA1
#define MSG_vector_match_first  "Errpr vector_match, .key != "STRING

#define MSG_vector_find_index      "Error vector_find_index, Expected != "MSG_INDEX
#define MSG_vector_find_index_fail "Error vecotr_find_index, Expected != -1"

#define MSG_vector_remove "Error vector_remove, .data[0] != NULL"

//////////////////////////////////////////////

static char* test_type_new_s() 
{
    mu_assert(MSG_type_new_s, strcmp(type_new_s(STRING).STR, STRING) == 0);
    return 0;
}

static char* test_type_new_i() 
{
    mu_assert(MSG_type_new_i, type_new_i(VALUE).INT == VALUE);
    return 0;
}

static char* test_dict_new() 
{
    Dict test_dict = dict_new(STRING, type_new_i(VALUE));
    mu_assert(MSG_dict_new_key, strcmp(test_dict.key, STRING) == 0);
    mu_assert(MSG_dict_new_value, test_dict.value.INT == VALUE);
    return 0;
}

//Currently not testing .data should equal sizeof(Dict)*capacity
static char* test_vector_new() 
{
    Vector test_vect = vector_new();
    mu_assert(MSG_vector_new_size, test_vect.size == 0);
    mu_assert(MSG_vector_new_capacity, test_vect.capacity == 2);
    vector_destroy(&test_vect);
    return 0;
}

///////////////////////////////////////////////

static char* test_vector_add() 
{
    Vector test_vect = vector_new();
    Dict test_dict = dict_new(STRING, type_new_i(VALUE));
    vector_add(test_dict, &test_vect);
    
    mu_assert(MSG_vector_add_key, strcmp(test_vect.data[0].key,STRING) == 0);
    mu_assert(MSG_vector_add_value, test_vect.data[0].value.INT == VALUE);
    mu_assert(MSG_vector_add_size, test_vect.size == 1);
    vector_destroy(&test_vect);

    return 0;
}

static char* test_vector_find() 
{
    Vector test_vect = Setup();
    
    Dict found_dict = vector_find(STRING, test_vect);
    Dict null_dict = vector_find("NONE", test_vect);

    mu_assert(MSG_vector_find, strcmp(found_dict.key, STRING) == 0);
    mu_assert(MSG_vector_find_null, strcmp(null_dict.key, "NULL") == 0);
    vector_destroy(&test_vect);

    return 0;
}

static char* test_vector_match() 
{
    Vector test_vect = Setup();

    Dict string_dict = vector_match(STRING, test_vect);
    Dict data_dict = vector_match(TDATA1, test_vect);
    //first does not match any in the vector,
    //so the match return the first element if none is found.
    Dict first_item = vector_match("FIRST", test_vect);

    mu_assert(MSG_vector_match_string, strcmp(string_dict.key, STRING) == 0);
    mu_assert(MSG_vector_match_tdata, strcmp(data_dict.key, TDATA1) == 0);
    mu_assert(MSG_vector_match_first, strcmp(first_item.key, STRING) == 0);
    vector_destroy(&test_vect);

    return 0;
}

static char* test_vector_find_index() 
{
    Vector test_vect = Setup();

    int test_index = vector_find_index(TDATA2, test_vect);
    int test_not_found = vector_find_index("FAIL", test_vect);

    mu_assert(MSG_vector_find_index, test_index == INDEX);
    mu_assert(MSG_vector_find_index_fail, test_not_found == -1);
    vector_destroy(&test_vect);

    return 0;
}

//Currently vector_remove only changes data to NULL.
//and the vector is not resized.
static char* test_vector_remove() 
{
    Vector test_vect = Setup();

    vector_remove(STRING, &test_vect);
    mu_assert(MSG_vector_remove, strcmp(test_vect.data[0].key,"NULL") == 0);
    vector_destroy(&test_vect);

    return 0;
}

///////////////////////////////////////////////
static Vector Setup() 
{
    Vector test_vect = vector_new();

    vector_add(
        dict_new(STRING, type_new_i(VALUE)), 
        &test_vect
    );
    
    vector_add(
        dict_new(TDATA1, type_new_i(VALUE)), 
        &test_vect
    );

    vector_add(
        dict_new(TDATA2, type_new_i(VALUE)), 
        &test_vect
    );

    vector_add(
        dict_new(TDATA3, type_new_i(VALUE)), 
        &test_vect
    );

    vector_add(
        dict_new(TDATA4, type_new_i(VALUE)), 
        &test_vect
    );

    return test_vect;
}

static char* all_tests() 
{
    mu_run_test(test_type_new_s);
    mu_run_test(test_type_new_i);
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
        printf("%s\n", result);
    }
    else {
        printf("ALL VECTOR TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
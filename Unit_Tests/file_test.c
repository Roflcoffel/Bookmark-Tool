#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../color.h"
#include "../vector.h"
#include "../file.h"
#include "minunit.h"

static char* test_file_write();
static char* test_file_read();

static char* all_tests();
static Vector Setup();

int tests_run = 0;

#define SERIE_KEY_0 "K-ON!"
#define SERIE_KEY_1 "Mahou Shoujo Lyrical Nanoha"
#define SERIE_KEY_2 "Clannad"

#define SERIE_VALUE_0 5
#define SERIE_VALUE_1 10
#define SERIE_VALUE_2 0

#define FILENAME "db.csv"

#define MSG_test_file_write "Error, test_file_write data should be "SERIE_KEY_0", "SERIE_KEY_1", "SERIE_KEY_2
#define MSG_test_file_read  "Error, test_file_read data should be "SERIE_KEY_0", "SERIE_KEY_1", "SERIE_KEY_2

static char* test_file_write()
{
	Vector db = Setup();

	file_write(FILENAME, db);
	printf("CALL file_write(%s, %s)\n\n", FILENAME, "db");

	printf("data[0].key is %s\ndata[1].key is %s\ndata[2].key is %s\n", db.data[0].key, db.data[1].key, db.data[2].key);
	mu_assert(MSG_test_file_write, strcmp(db.data[0].key, SERIE_KEY_0) == 0);
	mu_assert(MSG_test_file_write, strcmp(db.data[1].key, SERIE_KEY_1) == 0);
	mu_assert(MSG_test_file_write, strcmp(db.data[2].key, SERIE_KEY_2) == 0);

	printf("\ntest_file_write ");
	print_color(GREEN, "PASSED\n\n");

	return 0;
}

static char* test_file_read()
{
	Vector db = vector_new();

	file_read(FILENAME, &db);
	printf("CALL file_read(%s, %s)\n\n", FILENAME, "db");

	printf("data[0].key is %s\ndata[1].key is %s\ndata[2].key is %s\n", db.data[0].key, db.data[1].key, db.data[2].key);
	mu_assert(MSG_test_file_read, strcmp(db.data[0].key, SERIE_KEY_0) == 0);
	mu_assert(MSG_test_file_read, strcmp(db.data[1].key, SERIE_KEY_1) == 0);
	mu_assert(MSG_test_file_read, strcmp(db.data[2].key, SERIE_KEY_2) == 0);

	printf("\ntest_file_read ");
	print_color(GREEN, "PASSED\n");

	return 0;
}

static char* all_tests() 
{
	mu_run_test(test_file_write);
	mu_run_test(test_file_read);
    return 0;
}

static Vector Setup() 
{
    Vector test_vect = vector_new();

    vector_add(dict_new(SERIE_KEY_0, SERIE_VALUE_0), &test_vect);
    vector_add(dict_new(SERIE_KEY_1, SERIE_VALUE_1), &test_vect);
    vector_add(dict_new(SERIE_KEY_2, SERIE_VALUE_2), &test_vect);

    return test_vect;
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
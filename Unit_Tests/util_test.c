#include "../util.c"
#include "minunit.h"

int tests_run = 0;

static char* all_tests() {
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
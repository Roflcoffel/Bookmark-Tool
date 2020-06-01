//color.c
//Some basic function for colouring the output of printf
#include <stdio.h>
#include "size.h"
#include "color.h"

void print_color(char color[8], char text[S_SIZE])
{
        printf(color);
        printf(text);
        printf(RESET);
}
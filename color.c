//color.c
//Some basic function for colouring the output of printf
#include <stdio.h>
#include "color.h"

void print_color(char color[8], char text[])
{
        printf(color);
        printf(text);
        printf(RESET);
}
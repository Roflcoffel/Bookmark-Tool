//color.c
//Some basic function for colouring the output of printf
#include "color.h"

void print_color(char color[8], char text[255])
{
        printf(color);
        printf(text);
        printf(RESET);
}
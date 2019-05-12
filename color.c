//color.c
//Some basic function for colouring the output of printf

//Defined Colours
#define BLACK   "\033[0;30m"
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define WHITE   "\033[0;37m"

//reset colour
#define RESET   "\033[0m"

void print_color(char color[8], char text[255])
{
        printf(color);
        printf(text);
        printf(RESET);
}
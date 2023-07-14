#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_FONT_COL_RESET     "\x1b[0m"
#define FONT_COL_CUSTOM_RED     "\e[38;2;200;0;0m" // where rrr;ggg;bbb in 38;2;rrr;ggg;bbbm can go from 0 to 255 respectively
#define FONT_COL_CUSTOM_GREEN   "\e[38;2;0;200;0m" // where rrr;ggg;bbb in 38;2;rrr;ggg;bbbm can go from 0 to 255 respectively
#define FONT_COL_CUSTOM_BLUE    "\e[38;2;0;0;200m" // where rrr;ggg;bbb in 38;2;rrr;ggg;bbbm can go from 0 to 255 respectively
#define NIGHT_BLUE "\e[38;2;2;2;58m" // where rrr;ggg;bbb in 38;2;rrr;ggg;bbbm can go from 0 to 255 respectively"
#define BCKGRD_COL_CUSTOM_RED   "\e[48;2;200;0;0m" // where rrr;ggg;bbb in 48;2;rrr;ggg;bbbm can go from 0 to 255 respectively
#define BCKGRD_COL_CUSTOM_GREEN "\e[48;2;0;200;0m" // where rrr;ggg;bbb in 48;2;rrr;ggg;bbbm can go from 0 to 255 respectively
#define BCKGRD_COL_CUSTOM_BLUE  "\e[48;2;0;0;200m" // where rrr;ggg;bbb in 48;2;rrr;ggg;bbbm can go from 0 to 255 respectively

int main() {
	printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n");
	printf(NIGHT_BLUE         "This text is NIGHT_BLUE!"         ANSI_COLOR_RESET "\n");
	printf(FONT_COL_CUSTOM_RED     "This font color is CUSTOM_RED!"           ANSI_FONT_COL_RESET "\n");
	printf(FONT_COL_CUSTOM_GREEN   "This font color is CUSTOM_GREEN!"         ANSI_FONT_COL_RESET "\n");
	printf(FONT_COL_CUSTOM_BLUE    "This font color is CUSTOM_BLUE!"          ANSI_FONT_COL_RESET "\n");
	printf(BCKGRD_COL_CUSTOM_RED   "This background color is CUSTOM_RED!"     ANSI_FONT_COL_RESET "\n");
	printf(BCKGRD_COL_CUSTOM_GREEN "This background color is CUSTOM_GREEN!"   ANSI_FONT_COL_RESET "\n");
	printf(BCKGRD_COL_CUSTOM_BLUE  "This background color is CUSTOM_BLUE!"    ANSI_FONT_COL_RESET "\n");
	printf(FONT_COL_CUSTOM_GREEN BCKGRD_COL_CUSTOM_RED "This font color is CUSTOM_GREEN with background CUSTOM_RED!"    ANSI_FONT_COL_RESET "\n");
	printf("This font color is NORMAL!\n");
}
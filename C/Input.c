#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<winuser.h>
#include<wincon.h>
#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int getkey();

int getkey() {

    while (1) {
        // This checks if the window is focused
        if (GetForegroundWindow() != GetConsoleWindow()) continue;
        
        for (int i = 1; i < 255; ++i) {
            // The bitwise and selects the function behavior (look at doc)
            if (GetAsyncKeyState(i) & 0x07)
                return i;

        }

        Sleep(250);
    }
}

int main() {
    //while (1) {
       // int key = getkey();
      //  printf("Key: %d\n", key);
        /*
        Up: 38
        Down: 40
        Left: 37
        Right: 39
        W: 87
        A: 65
        S: 83
        D: 68

        */
        //}
    int key;
    char* user[] = { "Lewis Hamilton", "Charles Leclerc", "Max Verstappen" };
    int length = (int)(sizeof(user) / sizeof(user[0]));
    int current = 0;
    bool first = true;
    printf(ANSI_COLOR_CYAN "Choose a driver" ANSI_COLOR_RESET " (Use arrow keys to choose, 'q' to quit)\n");

    for (int i = 0; i < 3; i++) {
        if (i == current) printf(ANSI_COLOR_YELLOW " %s " ANSI_COLOR_RESET, user[i]);
        else printf(ANSI_COLOR_BLUE " %s " ANSI_COLOR_RESET, user[i]);
    }
    printf("\n");
    while (1) {
        key = _getch();
        if (key == 224 || key == 0) { // Check for extended key
            key = _getch();
            switch (key) {
                case 72:
                    printf("Up arrow key pressed\n");
                    break;
                case 80:
                    printf("Down arrow key pressed\n");
                    break;
                case 75:
                    //printf("Left arrow key pressed\n");
                    if (current != 0) current--;
                    break;
                case 77:
                    //printf("Right arrow key pressed\n");
                    if (current != length - 1) current++;
                    break;
                default:
                    break;
            }
            if (first) {
				first = false;
                fputs("\033[A\033[2K", stdout);
                rewind(stdout);

			}
            
            //printf("\r                                                ");
            printf("\r");
            for (int i = 0; i < 3; i++) {
                if (i == current) printf(ANSI_COLOR_YELLOW " %s " ANSI_COLOR_RESET, user[i]);
                else printf(ANSI_COLOR_BLUE " %s " ANSI_COLOR_RESET, user[i]);
            }
        }
        else if (key == 'q') {
            break;
        }
    }

}
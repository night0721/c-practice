#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>
#include "driver.h"
#include "../lib/colour.h"

#define MAX_LINE_LENGTH 256
#define MAX_DRIVERS 3

#define ENTER_KEY 13

int main() {
    FILE* drivers_file = fopen("drivers.txt", "r");
    if (drivers_file == NULL) {
		printf("Error opening drivers file!\n");
		exit(1);
	}
    
    char line[MAX_LINE_LENGTH];
    int count = 0;
    char* tokens[MAX_DRIVERS][4]; // assuming there are only 3 drivers to choose from, and each driver has 4 attributes (name, team, age, number)

    while (fgets(line, sizeof(line), drivers_file) != NULL && count < MAX_DRIVERS) {
        char* token;
        int i = 0;

        // Use strtok to split the line by the delimiter and store the tokens
        token = strtok(line, ",");
        while (token != NULL) {
            tokens[count][i] = strdup(token);
            token = strtok(NULL, ",");
            i++;
        }

        count++;
    }
    fclose(drivers_file);

    Driver drivers[MAX_DRIVERS];

    for (int i = 0; i < count; i++) {
        drivers[i].name = tokens[i][0];
        drivers[i].team = tokens[i][1];
        drivers[i].age = atoi(tokens[i][2]);
        drivers[i].number = atoi(tokens[i][3]);
    }

    int key;
    int current = 0;
    bool first = true;
    
    printf(ANSI_COLOR_CYAN "Choose a driver" ANSI_COLOR_RESET " (Use arrow keys to choose, 'q' to quit)\n");

    for (int i = 0; i < MAX_DRIVERS; i++) {
        if (i == current) printf(ANSI_COLOR_YELLOW " %s " ANSI_COLOR_RESET, drivers[i].name);
        else printf(ANSI_COLOR_BLUE " %s " ANSI_COLOR_RESET, drivers[i].name);
    }

    printf("\n");
    bool choosing_driver = true;
    while (choosing_driver) {
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
                    if (current != MAX_DRIVERS - 1) current++;
                    break;
                default:
                    break;
            }
            if (first) {
				first = false;
                fputs("\033[A\033[2K", stdout);
                rewind(stdout);
			}
            printf("\r");
            for (int i = 0; i < MAX_DRIVERS; i++) {
                if (i == current) printf(ANSI_COLOR_YELLOW " %s " ANSI_COLOR_RESET, drivers[i].name);
                else printf(ANSI_COLOR_BLUE " %s " ANSI_COLOR_RESET, drivers[i].name);
            }
        }
        else if (key == 'q') {
            break;
        }
        else if (key == ENTER_KEY) {
			printf("\n");
			printf("You chose: %s\n", drivers[current].name);
            choosing_driver = false;
			break;
		}
    }
    system("pause");
}
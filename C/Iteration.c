#include<stdio.h>
#include <stdlib.h>

void iteration(int lines);

int main() {
	printf("Drawing with iteration\n");
	iteration(5);
	system("pause");
}

void iteration(int lines) {
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < i + 1; j++) {
			printf("#");
		}
		printf("\n");
	}
}
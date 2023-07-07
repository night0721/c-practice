#include<stdio.h>
#include<stdlib.h>

void recursion(int lines);

int main() {
	printf("Drawing with recursion\n");
	recursion(5);
	system("pause");
}

void recursion(int lines) {
	if (lines == 0) return;
	recursion(lines - 1);
	for (int i = 0; i < lines; i++) {
		printf("#");
	}
	printf("\n");
}
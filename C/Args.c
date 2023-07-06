#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv) {
	printf("Arguments count: %i\n", argc);
	for (int i = 0; i < argc; i++) {
		printf("Argument %i: %s\n", i, argv[i]);
		int length = strlen(argv[i]);
		printf("Length: %d", length);
	}
}
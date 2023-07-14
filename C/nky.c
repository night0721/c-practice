#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	char path[] = "C:\\.nky\\Coding";
	int code = chdir(path);
	printf("code: %d\n", code);
	return 0;
}
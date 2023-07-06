#include<stdio.h>
#include<stdlib.h>

int main() {
	int x = 5;
	int *xptr = &x;
	printf("%p\n", xptr);
	printf("%d\n", *xptr); // dereferencing
}
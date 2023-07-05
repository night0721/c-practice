#include<stdio.h>
#include<stdlib.h>

typedef struct
{
	char* name;
	char* brand;
	int age;
}
car;

void printCars();

int main() {
	printf("Cars\n");
	printCars();
	system("pause");
}

void printCars() {
	car cars[3];
	cars[0].name = "NSX";
	cars[0].brand = "Honda";
	cars[0].age = 2;
	cars[1].name = "Corolla";
	cars[1].brand = "Toyota";
	cars[1].age = 5;
	cars[2].name = "Roadster";
	cars[2].brand = "Tesla";
	cars[2].age = 10;
	for (int i = 0; i < 3; i++) {
		printf("Name: %s\nBrand: %s\nAge: %i\n", cars[i].name, cars[i].brand, cars[i].age);
	}
}
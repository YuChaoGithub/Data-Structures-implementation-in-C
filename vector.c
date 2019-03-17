#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 5
int* array;
int curr_size = 0;
int max_size;

void init_array();
void resize_array(int);
void push_back(int);
void pop_back();
int back();
int is_empty();
int get_from_index(int);
void free_array();
void print();

int main(void) {
	init_array();
	push_back(3); print();
	push_back(5); print();
	push_back(7); print();
	push_back(3); print();
	push_back(4); print();
	push_back(1); print();
	printf("The back is %d.\n", back());
	pop_back(); print();
	pop_back(); print();
	printf("Is the array empty? %s\n", (is_empty() ? "Yes" : "No"));
	free_array();
	return 0;
}

void print() {
	int i;
	for (i = 0; i < curr_size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

void init_array() {
	array = (int *) malloc(sizeof(int) * INIT_SIZE);
	max_size = INIT_SIZE;
	printf("Array initialized. Max size: %d.\n", max_size);
}

void resize_array(int new_size) {
	int* temp = malloc(sizeof(int) * new_size);
	
	int i;
	for (i = 0; i < curr_size; i++) {
		temp[i] = array[i];
	}
	
	max_size = new_size;

	free(array);
	array = temp;
	
	printf("Array resized to size %d.\n", max_size);
}

void push_back(int i) {
	if (curr_size == max_size) {
		resize_array(max_size * 2);
	}
	
	array[curr_size] = i;
	curr_size++;

	printf("Pushed back %d. Curr size: %d / %d.\n", i, curr_size, max_size);
}

void pop_back() {
	if (curr_size == 0) {
		printf("Array already empty.\n");
	} else {
		curr_size--;
		printf("Popped back. Curr size: %d.\n", curr_size);
	}
}

int back() {
	if (curr_size == 0) {
		printf("Array empty.\n");
		return -1;
	}

	return array[curr_size - 1];
}

int get_from_index(int i) {
	if (i >= curr_size) {
		printf("Index out of bounds.\n");
		return -1;
	}

	return array[i];
}

int is_empty() {
	return curr_size == 0;
}

void free_array() {
	free(array);
}

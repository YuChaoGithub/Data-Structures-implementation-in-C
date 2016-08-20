#define INIT_SIZE 5
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef int elem_type;

typedef struct {
	elem_type *arr;
	size_t occupied;
	size_t size;
} array;

void init_array(array*,size_t);
size_t get_size(array*);
void clear(array*);
int is_empty(array*);
void push(array*, elem_type);
void pop(array*);
elem_type back(array*);
elem_type front(array*);
size_t capacity(array*);
elem_type* get_at(array*, size_t);
void reserve(array*, size_t);
void free_array(array*);
void print(array*);

void init_array(array* a, size_t size) {
	a->arr = (elem_type *) malloc(size * sizeof(elem_type));
	a->occupied = 0;
	a->size = size;
}

size_t get_size(array* a) {
	return a->occupied;
}

void clear(array* a) {
	a->occupied = 0;
}

int is_empty(array* a) {
	return a->occupied == 0 ? 1 : 0;
}

void push(array* a, elem_type x) {
	if (a->occupied == a->size)
		reserve(a, a->size * 2);
	(a->arr)[a->occupied++] = x;
}

void pop(array* a) {
	a->occupied--;
}

elem_type back(array* a) {
	return (a->arr)[a->occupied-1];
}

elem_type front(array* a) {
	return (a->arr)[0];
}

elem_type * get_at(array* a, size_t index) {
	return a->arr + index;
}

size_t capacity(array* a) {
	return a->size;
}

void reserve(array* a, size_t cap) {
	if (cap < a->size) return;
	elem_type* new_array = (elem_type*) malloc(sizeof(elem_type) * cap);

	int i;
	for (i = 0; i < a->occupied; i++) {
		new_array[i] = (a->arr)[i];
	}
	free(a->arr);
	a->arr = new_array;
	a->size = cap;
}

void free_array(array* a) {
	free(a->arr);
	a->occupied = 0;
	a->size = 0;
}

void print(array* a) {
	int i;
	printf("[");
	for (i = 0; i < a->occupied; i++) {
		printf("%d, ", (a->arr)[i]);
	}
	printf("]\n");
}

int main(void) {
	array * my_array;
	init_array(my_array, INIT_SIZE);
	printf("get_size: %zu\n", get_size(my_array));
	printf("is_empty: %d\n", is_empty(my_array));
	push(my_array, 3); printf("Push 3\n");
	push(my_array, 9); printf("Push 9\n");
	push(my_array, 10); printf("Push 10\n");
	print(my_array);
	printf("front: %d\n", front(my_array));
	printf("back: %d\n", back(my_array));
	push(my_array, 40); printf("Push 40\n");
	push(my_array, 3); printf("Push 3\n");
	printf("capacity: %zu\n", capacity(my_array));
	push(my_array, 30); printf("Push 30\n");
	print(my_array);
	*(get_at(my_array, 2)) = 190; printf("get_at(2) = 190\n");
	print(my_array);
	pop(my_array); printf("pop");
	print(my_array);
	free_array(my_array);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct _heap {
	int currSize;
	int maxSize;
	int* arr;
} Heap;

Heap* initHeap(int maxSize) {
	Heap* h = malloc(sizeof(Heap));
	h->currSize = 0;
	h->maxSize = maxSize;
	h->arr = malloc(sizeof(int) * (1 + maxSize));
	return h;
}

void freeHeap(Heap* h) {
	free(h->arr);
	free(h);
}

void percolateDown(Heap* h, int hole) {
	int val = h->arr[hole];
	
	int child;
	for (; hole * 2 <= h->currSize; hole = child) {
		child = hole * 2;
		if (child != h->currSize && h->arr[child + 1] < h->arr[child])
			child += 1;
		if (h->arr[child] < val)
			h->arr[hole] = h->arr[child];
		else break;
	}

	h->arr[hole] = val;
}

Heap* buildHeap(int* arr, int arrLen, int heapLen) {
	Heap* h = malloc(sizeof(Heap));
	h->maxSize = heapLen;
	h->currSize = arrLen;
	h->arr = malloc(sizeof(int) * (heapLen + 1));
	
	int i;
	for (i = 0; i < arrLen; i++)
		h->arr[i + 1] = arr[i];

	for (i = h->currSize / 2; i > 0; i--)
		percolateDown(h, i);
	
	return h;
}

int findMin(Heap* h) {
	if (h->currSize == 0) {
		puts("The heap is empty, cannot findMin.");
		return -1;
	}

	return h->arr[1];
}

void insert(Heap* h, int val) {
	if (h->currSize == h->maxSize) {
		puts("The heap is full, cannot insert.");
		return;
	}

	h->currSize++;

	int hole = h->currSize;
	for (; hole > 1 && h->arr[hole / 2] > val; hole /= 2)
		h->arr[hole] = h->arr[hole / 2];
	h->arr[hole] = val;
}

void deleteMin(Heap* h) {
	if (h->currSize == 0) {
		puts("The heap is empty, cannot deleteMin.");
		return;
	}
	
	h->arr[1] = h->arr[h->currSize];

	h->currSize--;

	percolateDown(h, 1);
}

void print(Heap* h) {
	int i;
	putchar('[');
	for (i = 1; i <= h->currSize; i++) {
		printf("%d ", h->arr[i]);
	}
	puts("]");
}

int main(void) {
	int arr[12] = {7, 4, 9, 3, 8, 5, 2, 67, 5, 1, 59, 53};
	Heap* h = buildHeap(arr, 12, 40);
	print(h);
	insert(h, 100);
	insert(h, 101);
	print(h);
	deleteMin(h);
	deleteMin(h);
	deleteMin(h);
	print(h);
	insert(h, 3);
	insert(h, 1);
	print(h);
	deleteMin(h);
	deleteMin(h);
	deleteMin(h);
	deleteMin(h);
	deleteMin(h);
	deleteMin(h);
	print(h);
	insert(h, 44);
	print(h);
	return 0;
}

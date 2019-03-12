#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int val;
	struct _node* next;
} Node;

typedef struct _queue {
	Node* head;
	Node* rear;
} Queue;

Queue* initQueue() {
	Queue* q = malloc(sizeof(Queue));
	q->head = malloc(sizeof(Node));
	q->rear = q->head;
	return q;
}

void freeQueue(Queue* q) {
	Node* n = q->head;
	while (n) {
		Node* temp = n->next;
		free(n);
		n = temp;
	}
	free(q);
}

int front(Queue* q) {
	if (q->head == q->rear) {
		puts("The queue is empty, there is no front.");
		return -1;
	}

	return q->head->next->val;
}

void push(Queue* q, int val) {
	Node* n = malloc(sizeof(Node));
	n->val = val;
	n->next = NULL;
	q->rear->next = n;
	q->rear = n;
}

void pop(Queue* q) {
	Node* n = q->head->next;
	if (!n) {
		puts("The queue is empty.");
		return;
	}

	if (n == q->rear)
		q->rear = q->head;

	q->head->next = n->next;
	free(n);
}

void print(Queue* q) {
	Node* n = q->head->next;
	putchar('[');
	while (n) {
		printf("%d ", n->val);
		n = n->next;
	}
	puts("]");
}

int main(void) {
	Queue* q = initQueue();
	push(q, 1);
	push(q, 2);
	push(q, 3);
	push(q, 4);
	push(q, 5);
	print(q);
	pop(q);
	pop(q);
	pop(q);
	puts("Popped 1, 2, 3.");
	print(q);
	push(q, 4);
	push(q, 5);
	push(q, 6);
	print(q);
	pop(q);
	pop(q);
	pop(q);
	pop(q);
	pop(q);
	print(q);
	return 0;
}

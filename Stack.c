#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int val;
	struct _node* next;
} Node;

typedef struct _stack {
	Node* head;
} Stack;

Stack* initStack() {
	Stack* stk = malloc(sizeof(Stack));
	stk->head = malloc(sizeof(Node));
	stk->head->next = NULL;
	return stk;
}

void freeStack(Stack* stk) {
	Node* n = stk->head;
	while (n) {
		Node* temp = n->next;
		free(n);
		n = temp;
	}
	free(stk);
}

int top(Stack* stk) {
	if (!stk->head->next) {
		puts("The stack is empty, not top.");
		return -1;
	}

	return stk->head->next->val;
}

void push(Stack* stk, int val) {
	Node* n = malloc(sizeof(Node));
	n->val = val;
	n->next = stk->head->next;
	stk->head->next = n;
}

void pop(Stack* stk) {
	Node* n = stk->head->next;
	if (!n) {
		puts("The stack is empty, cannot pop.");
		return;
	}

	stk->head->next = n->next;
}

void print(Stack* stk) {
	Node* n = stk->head->next;
	putchar('[');
	while (n) {
		printf("%d ", n->val);
		n = n->next;
	}
	puts("]");
}

int main(void) {
	Stack* stk = initStack();
	push(stk, 1);
	push(stk, 2);
	push(stk, 3);
	push(stk, 4);
	push(stk, 5);
	print(stk);
	pop(stk);
	pop(stk);
	pop(stk);
	print(stk);
	push(stk, 6);
	push(stk, 7);
	push(stk, 8);
	print(stk);
	pop(stk);
	pop(stk);
	pop(stk);
	pop(stk);
	pop(stk);
	print(stk);
	freeStack(stk);
	return 0;
}

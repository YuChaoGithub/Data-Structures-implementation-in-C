#include <stdio.h>
#include <stdlib.h>

typedef int elem_type;
typedef struct _list_node {
	struct _list_node * next;
	elem_type val;
} list_node;

list_node * create_head(void);
int get_size(list_node *);
void clear(list_node *);
int is_empty(list_node *);
void push_front(list_node *, elem_type val);
void push_back(list_node *, elem_type val);
void pop_front(list_node *);
void pop_back(list_node *);
elem_type back(list_node *);
elem_type front(list_node *);

list_node * create_head(void) {
	list_node * head = (list_node *) malloc(sizeof(list_node));
	head->next = NULL;
	return head;
}

int get_size(list_node * head) {
	int size = -1;
	while (head) {
		head = head->next;
		++size;
	}
	return size;
}

void clear(list_node * head) {
	while (head) {
		list_node * temp = head;
		head = head->next;
		free(temp);
	}
}

int is_empty(list_node * head) {
	if (head->next) return 0;
	else return 1;
}

void push_front(list_node * head, elem_type val) {
	list_node * new_node = (list_node *) malloc(sizeof(list_node));
	new_node->val = val;
	new_node->next = head->next;
	head->next = new_node;
}

void push_back(list_node * head, elem_type val) {
	while (head->next)
		head = head->next;
	list_node * new_node = (list_node *) malloc(sizeof(list_node));
	new_node->val = val;
	new_node->next = NULL;
	head->next = new_node;
}

void pop_front(list_node * head) {
	list_node * temp = head->next;
	head->next = head->next->next;
	free(temp);
}

void pop_back(list_node * head) {
	list_node * prev = head;
	while (head->next) {
		prev = head;
		head = head->next;
	}
	prev->next = NULL;
	free(head);
}

elem_type front(list_node * head) {
	return head->next->val;
}

elem_type back(list_node * head) {
	while (head->next)
		head = head->next;
	return head->val;
}

void print(list_node * head) {
	head = head->next;
	printf("[");
	while (head) {
		printf("%d  ", head->val);
		head = head->next;
	}
	printf("]\n");
}

int main(void) {
	list_node * head = create_head();
	push_back(head, 3); printf("push_back(3)\n");
	push_back(head, 5); printf("push_back(5)\n");
	push_front(head, 10); printf("push_front(10)\n");
	print(head);
	pop_back(head); printf("pop_back()\n");
	print(head);
	pop_front(head); printf("pop_front()\n");
	print(head);
	printf("size: %d\n", get_size(head));
	push_back(head, 12); printf("push_back(12)\n");
	push_back(head, 11); printf("push_back(11)\n");
	print(head);
	printf("front: %d\n", front(head));
	printf("back: %d\n", back(head));
	clear(head);
	return 0;
}
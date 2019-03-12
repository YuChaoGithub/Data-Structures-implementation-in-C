#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int val;
	struct _node* left;
	struct _node* right;
} Node;

Node* initNode(int val) {
	Node* n = malloc(sizeof(Node));
	n->val = val;
	n->left = n->right = NULL;
	return n;
}

Node* insert(Node* root, int val) {
	if (!root)
		return initNode(val);

	if (root->val > val)
		root->left = insert(root->left, val);
	else
		root->right = insert(root->right, val);

	return root;
}

int getMin(Node* root) {
	if (!root)
		return -1;

	if (!root->left)
		return root->val;
	
	return getMin(root->left);
}

Node* delete(Node* root, int val) {
	if (!root)
		return root;

	if (root->val > val) {
		root->left = delete(root->left, val);
	} else if (root->val < val) {
		root->right = delete(root->right, val);
	} else {
		if (!root->left) {
			Node* temp = root->right;
			free(root);
			return temp;
		}
		if (!root->right) {
			Node* temp = root->left;
			free(root);
			return temp;
		}

		// Two children.
		root->val = getMin(root->right);
		root->right = delete(root->right, root->val);
	}
	return root;
}

Node* find(Node* root, int val) {
	if (!root)
		return NULL;
	
	if (root->val > val)
		return find(root->left, val);
	else if (root->val < val)
		return find(root->right, val);
	else
		return root;

	return NULL;
}

void freeTree(Node* root) {
	if (!root) return;

	freeTree(root->left);
	freeTree(root->right);
	
	free(root);
}

void preorder(Node* n) {
	if (!n) return;

	printf("%d ", n->val);
	preorder(n->left);
	preorder(n->right);
}

void postorder(Node* n) {
	if (!n) return;
	
	postorder(n->left);
	postorder(n->right);
	printf("%d ", n->val);
}

void inorder(Node* n) {
	if (!n) return;
	
	inorder(n->left);
	printf("%d ", n->val);
	inorder(n->right);
}

int main(void) {
	Node* n = NULL;
	n = insert(n, 100);
	n = insert(n, 50);
	n = insert(n, 6);
	n = insert(n, 150);
	n = insert(n, 149);
	n = insert(n, 166);
	n = insert(n, 420);
	n = insert(n, 69);
	preorder(n); putchar('\n');
	postorder(n); putchar('\n');
	inorder(n); putchar('\n');
	n = delete(n, 150);
	n = delete(n, 100);
	n = delete(n, 166);
	preorder(n); putchar('\n');
	postorder(n); putchar('\n');
	inorder(n); putchar('\n');
	return 0;
}

#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
	int val;
	int height;
	struct _node* left;
	struct _node* right;
} Node;

int height(Node* n) {
	if (!n) return 0;
	return n->height;
}

int max(int x, int y) {
	return x > y ? x : y;
}

void updateHeight(Node* root) {
	root->height = 1 + max(height(root->left), height(root->right));
}

Node* leftRotate(Node* k2) {
	Node* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	updateHeight(k2);
	updateHeight(k1);
	return k1;
}

Node* rightRotate(Node* k2) {
	Node* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	updateHeight(k2);
	updateHeight(k1);
	return k1;
}

Node* initNode(int val) {
	Node* n = malloc(sizeof(Node));
	n->left = n->right = NULL;
	n->height = 1;
	n->val = val;
	return n;
}

Node* balance(Node* root) {
	if (!root)
		return root;

	int balance = height(root->left) - height(root->right);
	if (balance > 1) {
		if (height(root->left->left) >= height(root->left->right)) {
			root = rightRotate(root);
		} else {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
	} else if (balance < -1) {
		if (height(root->right->right) >= height(root->right->left)) {
			root = leftRotate(root);
		} else {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
	}

	return root;
}

Node* insert(Node* root, int val) {
	if (!root)
		return initNode(val);

	if (root->val > val) {
		root->left = insert(root->left, val);
	} else {
		root->right = insert(root->right, val);
	}

	updateHeight(root);
	return balance(root);
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
		if (root->right && root->left) {
			root->val = getMin(root->right);
			root->right = delete(root->right, root->val);
		} else {
			Node* temp = root;
			root = root->left ? root->left : root->right;
			free(temp);
		}
	}

	return balance(root);
}

void freeTree(Node* root) {
	if (!root) return;
	freeTree(root->left);
	freeTree(root->right);
	free(root);
}

void inorder(Node* root) {
	if (!root) return;
	inorder(root->left);
	printf("%d ", root->val);
	inorder(root->right);
}

void postorder(Node* root) {
	if (!root) return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->val);
}

void preorder(Node* root) {
	if (!root) return;
	printf("%d ", root->val);
	preorder(root->left);
	preorder(root->right);
}

void printAll(Node* root) {
	printf("Inorder: "); inorder(root); putchar('\n');
	printf("Preorder: "); preorder(root); putchar('\n');
	printf("Postorder: "); postorder(root); putchar('\n');
}

int main(void) {
	Node* n = NULL;
	n = insert(n, 5);
	n = insert(n, 4);
	n = insert(n, 3);
	printAll(n);
	n = insert(n, 6);
	n = insert(n, 20);
	printAll(n);
	n = insert(n, 19);
	printAll(n);
	n = delete(n, 3);
	n = delete(n, 4);
	n = delete(n, 5);
	printAll(n);
	n = insert(n, 16);
	n = insert(n, 15);
	printAll(n);
	n = insert(n, 1);
	n = insert(n, 5);
	printAll(n);
	freeTree(n);
	return 0;
}

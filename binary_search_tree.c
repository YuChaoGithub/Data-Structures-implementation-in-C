#include <stdio.h>
#include <stdlib.h>

typedef int elem_type;
typedef struct _node {
	elem_type val;
	struct _node * left;
	struct _node * right;
} tree_node;

tree_node * find(tree_node * root, elem_type x) {
	if (!root || root->val == x)
		return root;
	else if (root->val > x)
		return find(root->left, x);
	else
		return find(root->right, x);
}

tree_node * find_min(tree_node * root) {
	if (!root) return NULL;
	if (!root->left)
		return root;
	else
		return find_min(root->left);
}

tree_node * find_max(tree_node * root) {
	if (!root) return NULL;
	if (!root->right)
		return root;
	else
		return find_max(root->right);
}

tree_node * insert(tree_node * root, elem_type x) {
	if (!root) {
		tree_node * new_node = (tree_node *) malloc(sizeof(tree_node));
		new_node->left = new_node->right = NULL;
		new_node->val = x;
		return new_node;
	} else if (x < root->val) {
		root->left = insert(root->left, x);
	} else {
		root->right = insert(root->right, x);
	}
	return root;
}

tree_node * delete(tree_node * root, elem_type x) {
	if (!root) return NULL;

	if (x < root->val) {
		root->left = delete(root->left, x);
	} else if (x > root->val) {
		root->right = delete(root->right, x);
	} else {
		if (root->right && root->left) {
			tree_node * temp = find_min(root->right);
			root->val = temp->val;
			root->right = delete(root->right, temp->val);
		} else {
			tree_node * temp = root;
			root = (root->left == NULL)? root->right : root->left;
			free(temp);
		}
	}
	return root;
}

void print_inorder(tree_node * root) {
	if (!root) return;
	print_inorder(root->left);
	printf("%d ", root->val);
	print_inorder(root->right);
}

void print_preorder(tree_node * root) {
	if (!root) return;
	printf("%d ", root->val);
	print_preorder(root->left);
	print_preorder(root->right);
}

void print_postorder(tree_node * root) {
	if (!root) return;
	print_postorder(root->left);
	print_postorder(root->right);
	printf("%d ", root->val);
}

int main(void) {
	tree_node * root = NULL;
	root = insert(root, 4); printf("insert 4\n");
	insert(root, 2); printf("insert 2\n");
	insert(root, 6); printf("insert 6\n");
	insert(root, 8); printf("insert 8\n");
	insert(root, 5); printf("insert 5\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	delete(root, 6); printf("delete 6\n");
	delete(root, 5); printf("delete 5\n");
	delete(root, 2); printf("delete 2\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	insert(root, 9); printf("insert 9\n");
	insert(root, 2); printf("insert 2\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	printf("Find 2: "); printf("%s\n", find(root, 2) == NULL ? "Not Found" : "Found");
	printf("Find Min: %d\n", find_min(root)->val);
	printf("Find Max: %d\n", find_max(root)->val);
	return 0;
}
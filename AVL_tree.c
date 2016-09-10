#include <stdio.h>
#include <stdlib.h>

typedef int elem_type;
typedef struct _node {
	elem_type val;
	int height;
	struct _node * left;
	struct _node * right;
} tree_node;

int max(int x, int y) {
	return (x > y) ? x : y;
}

int get_height(tree_node * node) {
	if (!node) return -1;
	else return node->height;
}

tree_node * rotate_with_left(tree_node * node){
	tree_node * orig_left = node->left;
	node->left = orig_left->right;
	orig_left->right = node;

	/* update height */
	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	orig_left->height = max(get_height(orig_left->left), get_height(orig_left->right)) + 1;
	return orig_left;
}

tree_node * rotate_with_right(tree_node * node) {
	tree_node * orig_right = node->right;
	node->right = orig_right->left;
	orig_right->left = node;

	node->height = max(get_height(node->left), get_height(node->right)) + 1;
	orig_right->height = max(get_height(orig_right->left), get_height(orig_right->right)) + 1;
	return orig_right;
}

tree_node * double_rotate_with_right_child(tree_node * node) {
	node->right = rotate_with_left(node->right);
	node = rotate_with_right(node);
	return node;
}

tree_node * double_rotate_with_left_child(tree_node * node) {
	node->left = rotate_with_right(node->left);
	node = rotate_with_left(node);
	return node;
}

tree_node * balance(tree_node * node) {
	if (!node) return NULL;

	if (get_height(node->left) - get_height(node->right) > 1) {
		if (get_height(node->left->left) >= get_height(node->left->right))
			node = rotate_with_left(node); //situation 1
		else
			node = double_rotate_with_left_child(node); //situation 2
	} else if (get_height(node->right) - get_height(node->left) > 1) {
		if (get_height(node->right->right) >= get_height(node->right->left))
			node = rotate_with_right(node);  //situation 3
		else
			node = double_rotate_with_right_child(node); //situation 4
	}

	//update height
	node->height = max(get_height(node->left), get_height(node->right)) + 1;

	return node;
}

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
		new_node->height = 0;
		new_node->val = x;
		return new_node;
	} else if (x < root->val) {
		root->left = insert(root->left, x);
	} else {
		root->right = insert(root->right, x);
	}
	
	return balance(root);
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

	return balance(root);	
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
	root = insert(root, 2); printf("insert 2\n");
	root = insert(root, 6); printf("insert 6\n");
	root = insert(root, 8); printf("insert 8\n");
	root = insert(root, 9); printf("insert 9\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	root = delete(root, 6); printf("delete 6\n");
	root = delete(root, 9); printf("delete 9\n");
	root = delete(root, 2); printf("delete 2\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	root = insert(root, 3); printf("insert 3\n");
	root = insert(root, 2); printf("insert 2\n");
	root = insert(root, 1); printf("insert 1\n");
	printf("Preorder: "); print_preorder(root); putchar('\n');
	printf("Inorder: "); print_inorder(root); putchar('\n');
	printf("Postorder: "); print_postorder(root); putchar('\n');
	printf("Find 2: "); printf("%s\n", find(root, 2) == NULL ? "Not Found" : "Found");
	printf("Find Min: %d\n", find_min(root)->val);
	printf("Find Max: %d\n", find_max(root)->val);
	return 0;
}
struct tree_node {
	tree_node* left;
	tree_node* right;
	int data;
	tree_node(int v) : data(v), left(NULL), right(NULL) { }
};

void mirror(tree_node* root) {
	if (root == NULL) {
		return; 
	}
	mirror(root->left);
	mirror(root->right);
	std::swap(root->left, root->right);
}

void test() {
	tree_node n1 = new tree_node(1);
	tree_node n2 = new tree_node(2);
	tree_node n3 = new tree_node(3);

	n1->left = n2;
	n2->left = n3;

	mirror(n1);
	assert(n1->left == NULL);
	assert(n1->right == n2);
	assert(n2->left == NULL);
	assert(n2->right == n3);
}

int main() {
	test();
}
	
#include <iostream>
using namespace std;

struct node {
	int value;
	node *left;
	node *right;
};

class btree {
public:
	btree();
	void insert(int value);
	node *search(int value);
	void destroy_tree();
	void preorder();
	
private:
	void destroy_tree(node *leaf);
	void insert(int key, node *leaf);
	node *search(int key, node *leaf);
	void preorder(node *leaf);
	node *root;
};

btree::btree() {
	root = NULL;
}

void btree::destroy_tree(node *leaf) {
	if (leaf!=NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

void btree::preorder(node *leaf) {
	if (leaf!=NULL) {
	preorder(leaf->left);
	cout << leaf->value <<  " ";
	preorder(leaf->right);	
	}
}

void btree::insert(int key, node *leaf) {
	if (key < leaf->value) {
		if (leaf->left != NULL) {
			insert(key,leaf->left);
		} else {
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
		}
	}
	
	else if (key >= leaf->value) {
		if (leaf->right !=NULL) {
			insert(key,leaf->right);
		} else {
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->left = NULL;
			leaf->right->right = NULL;
		}
	}
}

node *btree::search(int key, node *leaf) {
	if (leaf!=NULL) {
		if (key==leaf->value) {
			return leaf;
		} else if (key < leaf->value) {
			return search(key, leaf->left);
		} else {
			return search(key, leaf->right);
		}
	} else {
		return NULL;
	}
}

node *btree::search(int key) {
	return search(key, root);
}

void btree::insert(int key) {
	if (root!=NULL) {
		insert(key, root);
	} else
	{
		root=new node;
		root->value=key;
		root->left=NULL;
		root->right=NULL;
	}
}

void btree::destroy_tree() {
	destroy_tree(root);
}

void btree::preorder() {
	preorder(root);
}

int main()
{
	btree mytree;
	
	mytree.insert(8);
	mytree.insert(2);
	mytree.insert(4);
	mytree.insert(9);
	mytree.insert(23);
	mytree.insert(0);
	mytree.insert(2);
	mytree.insert(43);
	mytree.preorder();

	return 0;
}

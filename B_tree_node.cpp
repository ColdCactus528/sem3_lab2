#include <iostream>
#include "line_string.cpp"
using std::to_string;

template <class Tkey, class Tdata> class Binar_tree {
public:
	struct tnode {
		Tkey key;
		Tdata data;
		tnode* left;
		tnode* right;
	};

	Binar_tree () {
		root = NULL;
	}

	void add_new_node(Tkey key, Tdata item) {
		if (root != NULL) {
			add_new_node(key, item, root);

		} else {
			root = new tnode;
			root->key = key;
			root->data = item;
			root->right = NULL;
			root->left = NULL;
			number += 1;
		} 

	}

	Tdata& find_data(Tkey key) {
		return find_tnode(key, root)->data;
	}

	Tdata find_data(Tkey key) const{
		return find_tnode(key, root)->data;
	}

	bool ContainsKey(Tkey key) {
		if (find_tnode(key, root) == NULL) 
			return false;
		else 
			return true;
	}

	Binar_tree* tree_extraction(Tkey key) {
		Binar_tree<Tkey, Tdata>* new_tree = new Binar_tree<Tkey, Tdata>;
		tnode* node = find_tnode(key, root);

		return copy_tree(new_tree, node);
	}

	bool find_tree(Binar_tree* tree) {
		return tree_comp(root, tree->root);
	} 

	string lRr_print() {
		string* s = new string;
		return lRr_print(root, s);
	}

	string lrR_print() {
		string* s = new string;
		return lrR_print(root, s);
	}

	string rRl_print() {
		string* s = new string;
		return rRl_print(root, s);
	}

	string rlR_print() {
		string* s = new string;
		return rlR_print(root, s);
	}

	string Rlr_print() {
		string* s = new string;
		return Rlr_print(root, s);
	}

	string Rrl_print() {
		string* s = new string;
		return Rrl_print(root, s);
	}

	void delete_node (Tkey key) {
		root = delete_node(key, root);
	}

	void destroy_tree() {
		destroy_tree(root);
	}

	int tree_size() const {
		return number;
	}
	~Binar_tree() {
		destroy_tree();
	}

private:
	void add_new_node(Tkey key, Tdata item, tnode* tree) {
		if (tree->key > key) {
			if (tree->left != NULL) {
				add_new_node(key, item, tree->left);

			} else {
				tree->left = new tnode;
				tree->left->key = key;
				tree->left->data = item;
				tree->left->left = NULL;
				tree->left->right = NULL;
				number += 1;
			}
		}

		if (key > tree->key) {
			if (tree->right != NULL) {
				add_new_node(key, item, tree->right);
			
			} else {
				tree->right = new tnode;
				tree->right->key = key;
				tree->right->data = item;
				tree->right->left = NULL;
				tree->right->right = NULL;
				number += 1;
			}

		}
	}

	tnode* find_tnode(Tkey key, tnode* tree) {
		if (tree != NULL) {
			if (key == tree->key) {
				return tree;
			}

			if (key > tree->key) {
				return find_tnode(key, tree->right);

			} else {
				return find_tnode(key, tree->left);
			}

		} else {
			return NULL;
		} 
	}

	tnode* find_tnode(Tkey key, tnode* tree)  const {
		if (tree != NULL) {
			if (key == tree->key) {
				return tree;
			}

			if (key > tree->key) {
				return find_tnode(key, tree->right);

			} else {
				return find_tnode(key, tree->left);
			}

		} else {
			return NULL;
		} 
	}

	Binar_tree* copy_tree(Binar_tree* tree, tnode* new_root) {
		if (new_root != NULL) {
			tree->add_new_node(new_root->key, new_root->data);
			copy_tree(tree, new_root->left);
			copy_tree(tree, new_root->right);
		}
		return tree;
	}

	bool tree_comp(tnode* node_0, tnode* node_1) {
		if ((node_0 == NULL) && (node_1 == NULL)) {
			return true;
		}
		if (node_1 != NULL) {
			tnode* node = find_tnode(node_1->key, node_0);
			if (node == NULL) {
				return false;
			} else {
				bool flag_0 = tree_comp(node->right, node_1->right);
				bool flag_1 = tree_comp(node->left, node_1->left);
				if ((flag_0 != false) && (flag_1 != false)) {
					return true;
				
				} else {
					return false;
				}
			}
		}
	}

	tnode* min_node(tnode* node) {
		tnode* currentnode = node;

		while ((currentnode != NULL) && (currentnode->left != NULL)) {
			currentnode = currentnode->left;
		}

		return currentnode;
	}

	tnode* delete_node(Tkey key, tnode* tree) {
		if (tree == NULL) {
			return tree;
		}

		if (key > tree->key) {
			tree->right = delete_node(key, tree->right);
			return tree;

		} else if (tree->key > key) {
			tree->left = delete_node(key, tree->left);
			return tree;
		}

		if (tree->left == NULL) {
			tnode* temp = tree->right;
			delete tree;
			return temp;
			
		} else if (tree->right == NULL) {
			tnode* temp = tree->left;
			delete root;
			return temp;
		
		} else {
			tnode* succParent = tree;
			tnode* succ = tree->right;

			while (succ->left != NULL) {
				succParent = succ;
				succ = succ->left;
			}

			if (succParent != tree) {
				succParent->left = succ->right;

			} else {
				succParent->right = succ->right;
			}

			tree->key = succ->key;

			delete succ;
			return tree;
		}
	} 

	string lRr_print(tnode* tree, string* s) {
		if (tree != NULL) {
			lRr_print(tree->left, s);
			*s = *s + to_string(tree->key) + " :: " + to_string(tree->data) + " ||| ";
			lRr_print(tree->right, s);
		}
		return *s;
	}

	string lrR_print(tnode* tree, string* s) {
		if (tree != NULL) {
			lrR_print(tree->left, s);
			lrR_print(tree->right, s);
			*s = *s + to_string(tree->key) + " :: " + to_string(tree->data) + " ||| ";
		}
		return *s;
	}

	string rRl_print(tnode* tree, string* s) {
		if (tree != NULL) {
			rRl_print(tree->right, s);
			*s = *s + to_string(tree->key) + " :: " + to_string(tree->data) + " ||| ";
			rRl_print(tree->left, s);
		}
		return *s;
	}

	string rlR_print(tnode* tree, string* s) {
		if (tree != NULL) {
			rlR_print(tree->right, s);
			rlR_print(tree->left, s);
			*s = *s + to_string(tree->key) + " :: " + to_string(tree->data) + " ||| ";
		}
		return *s;
	}

	string Rlr_print(tnode* tree, string* s) {
		if (tree != NULL) {
			*s = *s + to_string(tree->data) + " ||| ";
			Rlr_print(tree->left, s); 
			Rlr_print(tree->right, s);
		}
		return *s;
	}

	string Rrl_print(tnode* tree, string* s) {
		if (tree != NULL) {
			*s = *s + to_string(tree->key) + " :: " + to_string(tree->data) + " ||| ";
			Rrl_print(tree->right, s);
			Rrl_print(tree->left, s);
		}
		return *s;
	}

	void destroy_tree(tnode* tree) {
		if (tree != NULL) {
			destroy_tree(tree->left);
			destroy_tree(tree->right);
			delete tree; 
		}
	}

	tnode* root;
	int number = 0;
};
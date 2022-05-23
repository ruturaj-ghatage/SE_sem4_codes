//============================================================================
// Name        : 21129_mock_TBT.cpp
// Author      : Ruturaj Ghatage
// Version     : 1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * Create an inordered threaded binary tree and perform inorder and preorder traversal.
 */

#include <iostream>
using namespace std;

class Node {
private:
	int data;
	Node *left_child;
	Node *right_child;
	int l_bit;
	int r_bit;

public:
	Node() {
		data = 0;
		left_child = NULL;
		right_child = NULL;
		l_bit = 0;		// Indicates it doesnt have a left child
		r_bit = 0;		// Indicates it doesnt have a right child
	}

	Node(int data) {
		this->data = data;
		this->left_child = NULL;
		this->right_child = NULL;
		this->l_bit = 0;
		this->r_bit = 0;
	}

	friend class TBT;
};

class TBT {
private:
	Node *head;
	Node *root;

public:
	TBT() {
		head = NULL;
		root = NULL;
	}

	Node* get_root() {
		return root;
	}

	Node* get_head() {
		return head;
	}

	void create() {
		int data;

		cout << "Enter the data of the node: ";
		cin >> data;

		Node *newNode = new Node(data);

		if (root == NULL) {
			root = newNode;
			head = new Node();
			head->data = 0;
			head->left_child = root;
			head->right_child = head;
			root->left_child = head;
			root->right_child = head;
			root->l_bit = 0;	// 0 indicates it doesnt have a left child
			root->r_bit = 0;	// 0 indicates it doesnt have a right child
		} else {

			addNode(root, newNode);
		}
	}

	void addNode(Node *root, Node *newNode) {
		if (newNode->data > root->data) {
			if (root->r_bit == 0) {	// doesnt have a right child
				newNode->right_child = root->right_child;
				newNode->left_child = root;
				root->right_child = newNode;
				root->r_bit = 1;  // It now has a right child
//				cout << "ADDED RIGHT";
			} else {
				addNode(root->right_child, newNode);
			}
		} else if (newNode->data < root->data) {
			if (root->l_bit == 0) {	// Doesnt have a left child
				newNode->left_child = root->left_child;
				newNode->right_child = root;
				root->left_child = newNode;
				root->l_bit = 1;	// It now has a child
//				cout << "ADDED left";
			} else {
				addNode(root->left_child, newNode);
			}
		} else {
			cout << "Repeated elements cannot be added\n";
			return;
		}
	}

	void print_inorder(Node *temp, Node *head) {

		while (temp != head) {

			// Going to the left most node
			while (temp->l_bit == 1) {
				temp = temp->left_child;
			}

			cout << " " << temp->data;

			while (temp->r_bit == 0) {
				temp = temp->right_child;
				if (temp == head) {
					return;
				}
				cout << " " << temp->data;
			}

			temp = temp->right_child;
		}

	}

	void print_preorder(Node *temp, Node *head) {

		while (temp != head) {

			cout << " " << temp->data;

			// Going to the left most node
			while (temp->l_bit == 1) {
				temp = temp->left_child;
				cout << " " << temp->data;

			}

			while (temp->r_bit == 0) {
				temp = temp->right_child;
				if (temp == head) {
					return;
				}
			}

			temp = temp->right_child;
		}

	}

	bool search(int data, Node *temp) {
		int flag = 0;

		while (temp != head) {

			// Going to the left most node
			while (temp->l_bit == 1) {
				temp = temp->left_child;
			}

			if (temp->data == data) {
				flag = 1;
			}

			while (temp->r_bit == 0) {
				temp = temp->right_child;
				if (temp == head) {
					break;
				}
				if (temp->data == data) {
					flag = 1;
				}
			}

			temp = temp->right_child;
		}

		if (flag == 1) {
			return true;
		} else {
			return false;
		}

	}

	Node* delete_node(int data, Node *temp) {

			if (temp->data > data) {
				root->right_child = delete_node(data, root->right_child);
			} else if (temp->data < data) {
				root->left_child = delete_node(data, root->left_child);
			} else {
//				if(root->l_bit == 0){
//					root->right_child->left_child = root->left_child;
//				}else if(root->r_bit == 0){
//					root->left_child->right_child = root->right_child;
//				}else{
//					cout<<"Only leaf nodes deletable..\n";
//				}
				cout << "FPUND";
			}

	}
};

int main() {

	TBT obj;
//	Node *root = obj.get_root();
//	Node *head = obj.get_head();
//
//	obj.create();
//	obj.create();
//	obj.create();
//
//	obj.print_inorder(root, head);
//
//	cout << "Done";

	int choice = 0;

	while (choice != 5) {
		cout << "\n********************************************";
		cout
				<< "\n1. Add a new node\n2. Print inorder\n3. Print preorder\n4. Delete a node\n5. Exit\n";
		cout << "********************************************\n";

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			obj.create();

		}
			break;

		case 2: {

			Node *root = obj.get_root();
			Node *head = obj.get_head();

			obj.print_inorder(root, head);

		}
			break;

		case 3: {

			Node *root = obj.get_root();
			Node *head = obj.get_head();

			obj.print_preorder(root, head);

		}
			break;

		case 4: {

			Node *root = obj.get_root();
			int data = 0;

			cout << "Enter the data: ";
			cin >> data;

			bool found = obj.search(data, root);
			cout<<found<<endl;
			if(found == true){
				obj.delete_node(data, root);

			}else{
				cout<<"No such element presenttttttttttt....\n";
			}

		}
			break;
		case 5: {
			cout << "Exiting...\nThank you!!!!!!\n";
		}
			break;

		default: {
			cout << "Enter a valid choice\n";
			break;
		}
		}
	}

	return 0;
}
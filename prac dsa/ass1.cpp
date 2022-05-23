/*
Beginning with an empty binary BT, Construct binary BT by inserting the values in the order given. After constructing a binary BT perform following operations on it-

1.Perform inorder /preorder and post order traversal <-
2.Change a BT so that the roles of the left and right pointers are swapped at every node
3.Find the height of BT <-
4.Copy this BT to another [operator=]
5.Count number of leaves, number of internal nodes. 
6.Erase all nodes in a binary BT.
(implement both recursive and non-recursive methods)
*/

#include <iostream>

using namespace std;

class Node
{
private:
    char data;
    Node *left_child;
    Node *right_child;

public:
    Node()
    {
        data = ' ';
        left_child = NULL;
        right_child = NULL;
    }

    Node(char data)
    {
        this->data = data;
        left_child = NULL;
        right_child = NULL;
    }

    friend class tree;
};

template <typename T>
class stack
{
    struct Snode
    {
        Snode *next;
        T data;

        Snode()
        {
            data = 0;
            next = NULL;
        }

        Snode(T m)
        {
            data = m;
            next = NULL;
        }
    };

    Snode *top;

public:
    stack()
    {
        top = NULL;
    }

    bool isEmpty()
    {
        if (top == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // Process similar to adding node at the start
    void push(T val)
    {
        Snode *newnode;
        if (top == nullptr)
        {
            newnode = new Snode(val);
            top = newnode;
        }
        else
        {
            newnode = new Snode(val);
            newnode->next = top;
            top = newnode;
        }
    }

    T pop()
    {
        if (top == nullptr)
        {
            cout << "Stack is empty" << endl;
        }
        else
        {
            T val;
            val = top->data;
            Snode *ptr = top;
            top = top->next;
            // cout << "Element: " << ptr->data << " popped out successfully" << endl;
            delete ptr;
            return val;
        }
    }

    void display()
    {
        Snode *ptr = top;
        while (ptr != NULL)
        {
            cout << "Element are: " << ptr->data << endl;
            ptr = ptr->next;
        }
    }
};

class tree
{
private:
    Node *root = new Node();

public:
    tree() { root = NULL; }

    Node *create()
    {
        int choice;
        char data;
        int present = 1;
        cout << "Enter the data value (Enter 0 to come to above level): ";
        cin >> data;
        Node *root;

        if (data == '0')
        {
            return NULL;
        }
        root = new Node(data);

        cout << "Left of " << data << endl;
        root->left_child = create();
        cout << "Right of " << data << endl;
        root->right_child = create();

        return root;
    }

    void preOrder_Traversal(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            cout << root->data << "  ";
            preOrder_Traversal(root->left_child);
            preOrder_Traversal(root->right_child);
        }
    }

    void postOrder_Traversal(Node *root)
    {
        if (root != NULL)
        {
            postOrder_Traversal(root->left_child);
            postOrder_Traversal(root->right_child);
            cout << root->data << "  ";
        }
    }

    void inOrder_Traversal(Node *root)
    {
        if (root != NULL)
        {
            inOrder_Traversal(root->left_child);
            cout << root->data << "  ";
            inOrder_Traversal(root->right_child);
        }
    }

    void swap_roots(Node *root)
    {

        if (root == NULL || (root->left_child == NULL && root->right_child == NULL))
        {
            return;
        }

        Node *temp = root->left_child;
        root->left_child = root->right_child;
        root->right_child = temp;

        swap_roots(root->left_child);
        swap_roots(root->right_child);
    }

    int height_of_tree(Node *root)
    {

        if (root == NULL)
        {
            return 0;
        }

        int left_side_height = 0, right_side_height = 0;

        left_side_height = height_of_tree(root->left_child);
        right_side_height = height_of_tree(root->right_child);

        if (left_side_height > right_side_height)
        {
            return left_side_height + 1;
        }
        else
        {
            return right_side_height + 1;
        }
    }

    int internal_nodes(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        else if (root->left_child != NULL || root->right_child != NULL)
        {
            return 1 + internal_nodes(root->left_child) + internal_nodes(root->right_child);
        }
        else
        {
            return 0;
        }
    }

    int Leaf_Count(Node *root)
    {
        if (root == NULL)
        {
            return 0;
        }
        if (root->left_child == NULL && root->right_child == NULL)
        {
            return 1;
        }
        else
        {
            return Leaf_Count(root->left_child) + Leaf_Count(root->right_child);
        }
    }

    void delete_tree(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        else
        {
            delete_tree(root->left_child);
            delete_tree(root->right_child);

            delete root;
        }
    }

    void preOrder_Traversal_Iterative(Node *root)
    {

        stack<Node *> s;
        s.push(root);
        Node *pt = root;
        while (!s.isEmpty())
        {

            if (pt != NULL)
            {
                cout << pt->data << "  ";
                if (pt->right_child)
                {
                    s.push(pt->right_child);
                    pt = pt->left_child;
                }
                else
                {
                    pt = pt->left_child;
                }
            }
            else
            {
                pt = s.pop();
            }
        }
    }

    void postOrder_traversal_iterative(Node *root)
    {
        stack<Node *> st;
        stack<Node *> st2;
        Node *ptr = root;
        st.push(root);
        while (!st.isEmpty())
        {
            ptr = st.pop();
            st2.push(ptr);

            if (ptr->left_child)
            {
                st.push(ptr->left_child);
            }
            if (ptr->right_child)
            {
                st.push(ptr->right_child);
            }
        }

        while (!st2.isEmpty())
        {
            ptr = st2.pop();
            cout << ptr->data << "  ";
        }
    }

    void inOrder_traversal_iterative(Node *root)
    {
        stack<Node *> s;
        Node *ptr = root;
        while (!s.isEmpty() || ptr != NULL)
        {
            if (ptr != NULL)
            {
                s.push(ptr);
                ptr = ptr->left_child;
            }
            else
            {
                ptr = s.pop();
                cout << ptr->data << "  ";
                ptr = ptr->right_child;
            }
        }
    }

    Node *copy_BT(Node *root)
    {
        Node *temp = nullptr;
        if (root != nullptr)
        {
            temp = new Node();
            temp->data = root->data;
            temp->left_child = copy_BT(root->left_child);
            temp->right_child = copy_BT(root->right_child);
        }
        return temp;
    }
};

int main()
{
    int height = 0, cont = 0, internal_nodes = 0, leaf_node = 0;

    tree obj;
    Node *st, *copy;
    st = obj.create();

    int choice;

    while (choice != 14)
    {
        cout << "\n***************MENU**************\n1. Create a tree\n";
        cout << "2. Pre Order Traversal\n3. Post Order Traversal\n4. In Order Traversal\n5. Swap Roots\n6. Height of tree\n";
        cout << "7. Copy to another tree\n8. Number of Internal Nodes\n9. Number of leaf Nodes\n10. Delete tree\n11. Preorder Traversal Iterative\n";
        cout << "12. Postorder Traversal Iterative\n13. Inorder Traversal Iterative\n14. Exit\n";
        cout << "*********************************\n";
        cout << "Enter your Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (st != NULL)
            {
                cout << "Tree already present...\n";
            }
            else
            {
                st = obj.create();
            }
            break;

        case 2:
            if (st != NULL)
            {
                obj.preOrder_Traversal(st);
            }
            else
            {
                cout << "The tree is empty....\n";
            }
            break;

        case 3:
            if (st == NULL)
            {
                cout << "The tree is empty....\n";
            }
            else
            {
                obj.postOrder_Traversal(st);
            }
            break;

        case 4:
            if (st == NULL)
            {
                cout << "The tree is empty....\n";
            }
            else
            {
                obj.inOrder_Traversal(st);
            }
            break;

        case 5:
            obj.swap_roots(st);
            cout << "The nodes are swapped...\n";
            break;

        case 6:
            height = obj.height_of_tree(st);
            cout << "The height of the tree is: " << height;
            break;

        case 7:
            if (st == NULL)
            {
                cout << "The tree is empty....\n";
            }
            else
            {
                copy = obj.copy_BT(st);
                cout << "The tree is copied into another tree: \n";
                cout << "The preorder travesal of copied tree is: \n";
                obj.preOrder_Traversal(copy);
            }
            break;

        case 8:
            internal_nodes = obj.internal_nodes(st);
            cout << "The number of Internal nodes are: " << internal_nodes;
            break;

        case 9:
            leaf_node = obj.Leaf_Count(st);
            cout << "The number of leaf nodes are: " << leaf_node;
            break;

        case 10:
            if (st != NULL)
            {
                obj.delete_tree(st);
                cout << "Tree Deleted..\n";
                cout << "Do you want to create another tree: (1/0): ";
                cin >> cont;
                if (cont == 1)
                {
                    st = obj.create();
                }
                else
                {
                    cout << "Not creating a tree...\n";
                    st = NULL;
                }
            }
            else
            {
                cout << "Create a tree first...\n";
            }
            break;

        case 11:
            obj.preOrder_Traversal_Iterative(st);
            // obj.test(st);
            break;

        case 12:
            obj.postOrder_traversal_iterative(st);
            break;

        case 13:
            obj.inOrder_traversal_iterative(st);
            break;

        case 14:
            cout << "Exiting....\nThank you";
            break;

        default:
            cout << "Enter a valid choice...\n";
            break;
        }
    }

    return 0;
}

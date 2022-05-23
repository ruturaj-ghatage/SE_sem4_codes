//============================================================================
// Name        : Assignment_2_BST.cpp
// Author      : Ruturaj Sanjay Ghatage
// Version     : 1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data
sorted in ascending/ Descending order. Also find how many maximum comparisons may require
for finding any keyword. Use Binary Search Tree for implementation.
*/

#include <iostream>
#include <string>
#define SPACE 10

using namespace std;

class Node
{
private:
    Node *left_child;
    Node *right_child;
    string word;
    string def;

public:
    Node()
    {
        left_child = NULL;
        right_child = NULL;
        word = " ";
        def = " ";
    }

    Node(string word, string def)
    {
        this->word = word;
        this->def = def;
        this->left_child = NULL;
        this->right_child = NULL;
    }

    friend class BST;
};

class BST
{
    Node *root;

public:
    BST() { root = NULL; }

    bool isEmpty()
    {
        if (root == NULL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void insert_node(Node *newNode)
    {
        if (root == NULL)
        {
            root = newNode;
        }
        else
        {
            Node *temp = root;

            while (temp != NULL)
            {

                if (newNode->word == temp->word)
                {
                    cout << "Value already exists....\n";
                    return;
                }
                else if ((newNode->word < temp->word) && (temp->left_child == NULL))
                {
                    temp->left_child = newNode;
                    break;
                }
                else if ((newNode->word < temp->word) && (temp->left_child != NULL))
                {
                    temp = temp->left_child;
                }
                else if ((newNode->word > temp->word) && (temp->right_child == NULL))
                {
                    temp->right_child = newNode;
                    break;
                }
                else if ((newNode->word > temp->word) && (temp->right_child != NULL))
                {
                    temp = temp->right_child;
                }
            }
        }
    }

    void updating_dict(string word_name)
    {

        Node *temp = root;
        string meaning;

        while (temp->word != word_name)
        {
            if (word_name == temp->word)
            {
                break;
            }
            else if ((word_name < temp->word) && (temp->left_child != NULL))
            {
                temp = temp->left_child;
            }
            else if ((word_name > temp->word) && (temp->right_child != NULL))
            {
                temp = temp->right_child;
            }
        }

        cout << "Enter the updated meaning of the word: ";
        cin.clear();
        getline(cin, meaning);

        temp->def = meaning;
        cout << "Dictionary Updated...\n";
    }

    void print(Node *root, int space)
    {
        if (root == NULL)
        {
            return;
        }
        space += SPACE;
        print(root->right_child, space);
        cout << endl;
        for (size_t i = SPACE; i < space; i++)
        {
            cout << " ";
        }
        cout << root->word << " : " << root->def << endl;
        print(root->left_child, space);
    }

    Node *get_root()
    {
        return root;
    }

    Node *minValue(Node *root)
    {
        Node *current = root;

        while (current->left_child != NULL)
        {
            current = current->left_child;
        }
        return current;
    }

    Node *deleteNode(Node *root, string word_name)
    {

        if (root == NULL)
        {
            return NULL;
        }

        else if (word_name < root->word)
        {
            root->left_child = deleteNode(root->left_child, word_name);
        }

        else if (word_name > root->word)
        {
            root->right_child = deleteNode(root->right_child, word_name);
        }

        else
        {

            if (root->left_child == NULL)
            {
                Node *temp = root->right_child;
                delete root;
                return temp;
            }

            else if (root->right_child == NULL)
            {
                Node *temp = root->left_child;
                delete root;
                return temp;
            }

            else
            {

                Node *temp = minValue(root->right_child);
                root->word = temp->word;
                root->right_child = deleteNode(root->right_child, temp->word);
            }
        }

        return root;
    }

    void ascendingOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        ascendingOrder(root->left_child);
        cout << root->word << " : " << root->def << endl;
        ascendingOrder(root->right_child);
    }

    void descendingOrder(Node *root)
    {
        if (root == NULL)
        {
            return;
        }
        descendingOrder(root->right_child);
        cout << root->word << " : " << root->def << endl;
        descendingOrder(root->left_child);
    }

    bool checkPresent(string word_name)
    {
        Node *temp = root;
        int cmp=0;
        while (temp != NULL)
        {
            if (word_name == temp->word)
            {
                return true;
            }
            else if (word_name < temp->word)
            {
                temp = temp->left_child;
                cmp++;
            }
            else if (word_name > temp->word)
            {
                temp = temp->right_child;
                cmp++;
            }
        }
        cout<<"The number of comparisions performed: "<<cmp<<endl;
        return false;
    }

    void findingComp(string word_name)
    {
        Node *temp = root;
        int comp = 0;

        while (temp != NULL)
        {
            if (word_name == temp->word)
            {
                cout << "The number of Comparisons is: " << comp << endl;
                return;
            }
            else if ((word_name < temp->word) && (temp->left_child != NULL))
            {
                temp = temp->left_child;
                comp++;
            }
            else if ((word_name > temp->word) && (temp->right_child != NULL))
            {
                temp = temp->right_child;
                comp++;
            }
        }

        cout << "The number of Comparisons is: " << comp << endl;
    }
};

int main()
{
    BST obj;
    Node *root;
    Node *temp;

    string data, defn, word_name;
    int comp;

    int choice = 0;

    while (choice != 8)
    {
        cout << "*****************MENU*******************\n";
        cout << "1. Add a word to dictionary\n2. Traverse the tree\n3. Update a value from dictionary\n4. Delete a word from dictionary";
        cout << "\n5. Print dictionary in ascending order\n6. Print dictionary in descending order\n7. Comparisions to find a word\n8. Exit\n";
        cout << "****************************************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the word of the dictionary (Enter 0 to stop):\n";
            cin.clear();
            cin.ignore();
            getline(cin, data);

            if (data == "0")
            {
                break;
            }

            cout << "Enter the definition of the word: ";
            cin.clear();
            getline(cin, defn);
            temp = new Node(data, defn);

            obj.insert_node(temp);

            break;

        case 2:
            root = obj.get_root();
            obj.print(root, SPACE);
            break;

        case 3:
            cout << "Enter the word in the dict you want to update...\n";
            cin.clear();
            cin.ignore();
            getline(cin, word_name);

            if (obj.checkPresent(word_name) == true)
            {
                obj.updating_dict(word_name);
            }
            else
            {
                cout << "No Word Exists in the Dictionary....\n";
            }

            break;

        case 4:
            cout << "Enter the word in the dict you want to delete...\n";
            root = obj.get_root();
            cin.clear();
            cin.ignore();
            getline(cin, word_name);

            if (obj.checkPresent(word_name) == true)
            {
                obj.deleteNode(root, word_name);
            }
            else
            {
                cout << "No Word Exists in the Dictionary....\n";
            }
            break;

        case 5:
            root = obj.get_root();
            if (root != NULL)
            {
                root = obj.get_root();
                obj.ascendingOrder(root);
            }
            else
            {
                cout << "Enter items in dictionary first...\n";
            }
            break;

        case 6:
            root = obj.get_root();
            if (root != NULL)
            {
                root = obj.get_root();
                obj.descendingOrder(root);
            }
            else
            {
                cout << "Enter items in dictionary first...\n";
            }
            break;

        case 7:

            root = obj.get_root();
            if (root != NULL)
            {
                cout << "Enter the word in the dict you want to find...\n";
                cin.clear();
                cin.ignore();
                getline(cin, word_name);
                if (obj.checkPresent(word_name) == true)
                {
                    obj.findingComp(word_name);
                }
                else
                {
                    cout << "No Word Exists in the Dictionary....\n";
                }
            }
            else
            {
                cout << "Enter items in dictionary first...\n";
            }
            break;

        case 8:
            cout << "Exiting.....\nThank You!!!!\n";
            break;

        default:
            break;
        }
    }

    return 0;
}
#include <iostream>
#include <string>

#define SIZE 5

using namespace std;

class Node
{
private:
    string name;
    string mean;
    Node *next;

public:
    Node()
    {
        name = "";
        mean = "";
        next = NULL;
    }

    Node(string name, string mean)
    {
        this->name = name;
        this->mean = mean;
        this->next = NULL;
    }

    friend class linkedList;
};

class linkedList
{
private:
    Node *start;
    Node *last;

public:
    linkedList()
    {
        start = NULL;
        last = NULL;
    }

    void insert_at_end(string name, string mean)
    {
        if (start == NULL)
        {
            Node *temp = new Node(name, mean);
            start = temp;
            last = temp;
        }
        else
        {
            Node *temp = new Node(name, mean);
            Node *last = start;

            while (last->next != NULL)
            {
                last = last->next;
            }

            last->next = temp;
            last = temp;
        }
    }

    bool present(string w_name)
    {
        Node *temp = start;

        while (temp != NULL)
        {
            if (temp->name == w_name)
            {
                return true;
            }
            temp = temp->next;
        }

        return false;
    }

    void display_ll(int n)
    {
        if (start == NULL)
        {
            return;
        }
        else
        {
            Node *temp = start;
            cout << n << " => ";

            while (temp != NULL)
            {
                if (temp->name != "")
                {
                    cout << temp->name << " : " << temp->mean << " | ";
                }
                temp = temp->next;
            }
            cout << endl;
        }
    }

    void delete_node(string name)
    {
        if (start == NULL)
        {
            return;
        }
        else
        {
            Node *temp = start;
            Node *temp1 = start->next;

            if (temp->name == name)
            {
                temp->name = "";
                temp->mean = "";
                return;
            }

            while (temp1->next != NULL)
            {
                if (temp1->name == name)
                {
                    break;
                }
                temp = temp->next;
                temp1 = temp1->next;
            }

            temp->next = temp1->next;
            return;
        }
    }

    friend class dictionary;
};

class dictionary
{
private:
    linkedList dict[SIZE];

public:
    int hash_func(string name)
    {

        int sum = 0;

        for (int i = 0; i < name.length(); i++)
        {
            sum += name[i];
        }

        int hi = sum % SIZE;
        return hi;
    }

    void insert_word(string name, string mean)
    {
        int hash_key = hash_func(name);
        // cout<<hash_key<<endl;

        dict[hash_key].insert_at_end(name, mean);
    }

    void display()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            dict[i].display_ll(i);
        }
    }

    bool search(string name)
    {
        int hash_key = hash_func(name);
        bool check;

        check = dict[hash_key].present(name);

        return check;
    }

    void deletion(string name)
    {
        bool check = search(name);
        int hash_key = hash_func(name);

        if (check == true)
        {
            dict[hash_key].delete_node(name);
        }
        else
        {
            cout << "The word is not present in the dictionary....\n";
        }
    }
};

int main()
{

    // linkedList l1;

    // l1.display_ll();
    // l1.insert_at_end("1","1");
    // l1.display_ll();
    // l1.insert_at_end("2","2");
    // l1.insert_at_end("3","3");
    // l1.display_ll();

    // bool b1 = l1.present("1");
    // cout<<"b1: "<<b1<<endl;

    // bool b2 = l1.present("5");
    // cout<<"b2: "<<b2<<endl;

    // dictionary rutu;

    // rutu.insert_word("1", "1");
    // rutu.insert_word("2", "2");
    // // rutu.display();

    // rutu.insert_word("E", "3");
    // rutu.display();

    // rutu.deletion("E");
    // rutu.display();
    // rutu.search("11");
    // rutu.deletion("7");

    int choice = 0;
    dictionary rutu;

    while (choice != 5)
    {
        cout << "\n\n**********************************\n";
        cout << "1. Add a word\n2. Display the dictionary\n3. Search a word\n4. Delete a word\n5. Exit\n";
        cout << "**********************************\n\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name = "";
            string mean = "";
            cout << "Enter the word: ";
            cin >> name;

            cout << "Enter it's meaning: ";
            cin >> mean;
            rutu.insert_word(name, mean);
        }
        break;

        case 2:
        {
            rutu.display();
        }
        break;

        case 3:
        {
            string name = "";
            cout << "Enter the word: ";
            cin >> name;

            bool check = rutu.search(name);
            int hash_key = rutu.hash_func(name);

            if (check == true)
            {
                cout << "Element found with key: " << hash_key << endl;
            }
            else
            {
                cout << "Element not found in the dictionary\n";
            }
        }
        break;

        case 4:
        {
            string name = "";
            cout << "Enter the word: ";
            cin >> name;

            bool check = rutu.search(name);
            int hash_key = rutu.hash_func(name);

            if (check == true)
            {
                rutu.deletion(name);
            }
            else
            {
                cout << "Element not found in the dictionary\n";
            }
        }
        break;

        default:
            cout << "Enter a valid choice...\n";
            break;
        }
    }

    return 0;
}
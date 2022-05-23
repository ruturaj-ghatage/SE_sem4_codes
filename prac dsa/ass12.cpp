/*
 * Assignment 12
 *
 * Department maintains  a student information. The file contains roll number, name, division and address. Allow user to add, delete
 * information of student. Display information of particular employee. If record of student does not exist an appropriate message is
 * displayed. If it is, then the system displays the student details. Use sequential file to maintain the data.
 *
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
using namespace std;

class student
{
    int roll;
    string a, name, add;
        int n;
    char fname[20];


    public:
    ifstream fin;
    ofstream fout;
    fstream fm;


    void create()
    {
        int i;
        student s;
        cout << "Enter the name of file:- ";
        cin >> fname;
        fm.open(fname, ios::out);
        cout << "Enter no. of records:- ";
        cin >> n;
        for (i = 0; i < n; i++)
        {
            cout << "Enter the roll no:- ";
            cin >> s.roll;
            cout << "Enter the name:- ";
            cin >> s.name;
            cout << "Enter division:- ";
            cin >> s.a;
            cout << "Enter address:- ";
            cin >> s.add;
            fm.write((char *)&s, sizeof(s));
        }
        fm.close();
    }
    void display()
    {
        int i;
        student s;
        fin.open(fname);
        // cout << "\n Roll no\tNAME\tDIV\tADDRESS";

        for (i = 0; i < n; i++)
        {
            fin.read((char *)&s, sizeof(s));
            cout << "\n"
                 << s.roll << "\t" << s.name << "\t" << s.a << "\t" << s.add;
        }
        fin.close();
    }
    void insert()
    {
        student s;
        fout.open(fname, ios::app);
        cout << "Enter the roll no:- ";
        cin >> s.roll;
        cout << "Enter the name:- ";
        cin >> s.name;
        cout << "Enter the division:- ";
        cin >> s.a;
        cout << "Enter the address:- ";
        cin >> s.add;
        fout.write((char *)&s, sizeof(s));
        n++;
        fout.close();
    }
    void search(int key)
    {
        student s;
        int flag = 0, i;
        fin.open(fname);
        for (i = 0; i < n; i++)
        {
            fin.read((char *)&s, sizeof(s));
            if (s.roll == key)
            {
                cout << "\nRecord is present their corresponding details are:\nRoll no: ";
                cout << s.roll << "\nName: " << s.name << "\nDivision: " << s.a << "\nAddress: " << s.add;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            cout << "\nRoll no " << key << "is not present in your records";
        fin.close();
    }
    void deletem(int key)
    {

        student s;
        int flag = 0, i;
        fin.open(fname);
        fout.open("temp.txt", ios::out);

        for (i = 0; i < n; i++)
        {
            fin.read((char *)&s, sizeof(s));
            if (s.roll == key)
            {
                cout << "\nRecord deleted successfully";
                flag = 1;
            }
            else
            {
                fout.write((char *)&s, sizeof(s));
            }
        }
        if (flag == 0)
            cout << "\nRoll no " << key << "is not present in the record";
        else
            n--;
        fin.close();
        fout.close();
        remove(fname);
        rename("temp.txt", fname);
    }
};


int main()
{
    int ch, x;
    student obj;

    while (ch != 6)
    {
        cout << "\n********MENU******* " << endl
             << "\n1.Create\n2.Display\n3.Insert\n4.Search\n5.Delete\n6.Exit\nEnter your choice:- ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            obj.create();
            break;
        case 2:
            obj.display();
            break;
        case 3:
            obj.insert();
            break;
        case 4:
            cout << "Enter roll no. to search:- ";
            cin >> x;
            obj.search(x);
            break;
        case 5:
            cout << "Enter roll no. to delete:- ";
            cin >> x;
            obj.deletem(x);
            break;
        case 6:
            cout << "Exiting\nThank you!!!!\n";
            break;
        default:
            cout << "Enter a valid choice.....\n";
            break;
        }
    }

    return 0;
}
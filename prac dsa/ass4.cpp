//============================================================================
// Name        : Assignment_4_Hash.cpp
// Author      : Ruturaj Ghatage
// Version     : 1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
 * Consider a telephone book database of N clients. Make use of a hash table implementation to quickly look up client's telephone
 * number. make use of hash.
 */

#include <iostream>
#include <string>
#define SIZE 5

using namespace std;

class HashEntry {
private:
	long int tel;
	string name;
public:
	HashEntry() {
		tel = 0;
		name = " ";
	}
	HashEntry(long int tel, string name) {
		this->tel = tel;
		this->name = name;
	}
	friend class Tel_dir;
};

class Tel_dir {
private:
	HashEntry dir[SIZE];
	int size_r = 0;
	int size = 0;

public:
	int hash_func(long int key) {

		int hi = key % SIZE;
		return hi;

	}

	void insert(long int key, string name) {
		int max = SIZE;

		HashEntry obj = HashEntry(key, name);

		if (size_r >= max) {
			cout << "The table is full" << endl;
			return;
		}

		int hash_key = hash_func(key);

		if (dir[hash_key].tel != 0) {
			hash_key = (hash_key + 1) % SIZE;
			while (dir[hash_key].tel != 0) {
				hash_key = (hash_key + 1) % SIZE;
			}
			dir[hash_key] = obj;
		} else {
			dir[hash_key] = obj;

		}

		size_r++;
	}

	int search(long int key) {

		int flag = 0;

		int hkey = hash_func(key);

		while (dir[hkey].tel != 0) {
			if (dir[hkey].tel == key) {
				flag = 1;

				break;
			} else {
				hkey = hash_func(key + 1);
			}
		}

		if (flag == 1) {
			cout << hkey << " -> " << dir[hkey].tel << " : " << dir[hkey].name
					<< endl;
			return hkey;
		} else {
			cout << "Not present in directory....\n";
		}
	}

	void insert_rep(long int key, string name) {
		HashEntry obj = HashEntry(key, name);
		HashEntry obj1;

		if (size >= SIZE) {
			cout << "The table is full" << endl;
			return;
		}

		int hash_key = hash_func(key);

		if (dir[hash_key].tel != 0) {
			if (hash_key == hash_func(dir[hash_key].tel)) {
				hash_key = (hash_key + 1) % SIZE;
				while (dir[hash_key].tel != 0) {
					hash_key = (hash_key + 1) % SIZE;
				}
				dir[hash_key] = obj;
			} else {
				obj1 = dir[hash_key];
				dir[hash_key] = obj;
				key = obj1.tel;
				hash_key = hash_func(key);

				while (dir[hash_key].tel != 0) {
					hash_key = (hash_key + 1) % SIZE;
				}
				cout << hash_key;
				dir[hash_key] = obj1;

			}}
			else {
				dir[hash_key] = obj;
			}

			size++;
		}

	void display() {
		for (int i = 0; i < SIZE; i++) {

			if (dir[i].tel != 0) {
				cout << i << " -> " << dir[i].tel << " : " << dir[i].name
				<< endl;
			}
		}
	}



}
;

int main() {

	Tel_dir rep, w_rep;

	int choice;
	HashEntry obj;

	while (choice != 4) {
		cout << "\n**********MAIN MENU***********\n";
		cout
				<< "1. Insert a new entry \n2. Print the directory\n3. Search\n";
		cout << "4. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			string value = "";
			long int tel_no = 0;
			cout << "Enter the telephone number: ";
			cin >> tel_no;

			cout << "Enter the name: ";
			cin.clear();
			cin.ignore(1, '\n');
			getline(cin, value);
			cout << "SADASD";
			rep.insert(tel_no, value);
			w_rep.insert_rep(tel_no, value);
			break;
		}
		case 2: {
			cout << "The telephone Directory without replacement is: \n";
			rep.display();
			cout << endl << endl;
			cout << "The telephone Directory with replacement is: \n";
			w_rep.display();
			break;
		}
		case 3: {
			long int key;
			int comp, w_comp;
			cout << "Enter the number: ";
			cin >> key;
			comp = rep.search(key);
			w_comp = w_rep.search(key);
			cout
					<< "The number of comparisons in without replacement table is: "
					<< comp << endl;
			cout << "The number of comparisons in with replacement table is: "
					<< w_comp << endl;
			break;
		}
		case 4: {
			cout << "Exiting\nThank you!!!!!!\n";
			break;
		}
		default: {
			cout << "Enter a valid choice.....\n";
			break;
		}
		}
	}

	return 0;
}
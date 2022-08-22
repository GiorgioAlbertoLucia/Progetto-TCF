#include "include_t/fileFactory_t.hpp"

#include <iostream>
#include <string>

using namespace std;

void menu();

void file_submenu();

int main() {
	menu();

	TxtFile txtfile("data/text.txt");

	return 0;
}

void menu() {
	int choice;
	do {
		cout << "Enter the corresponding number:\n"
				"1. File handling\n";
		cin >> choice;
	} while (choice <= 0 && choice > 1);

	switch (choice) {
		case 1:
			file_submenu();
	}
}

void file_submenu() {
	string path;
	cout << "Open file" << endl;
	cout << "Enter file path" << endl;
	cin >> path;


}
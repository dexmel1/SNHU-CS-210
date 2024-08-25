/*	
	Dexter Melton
	CS-210
	Project 3
	08/13/2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

class GroceryTracker{
	
private:
	//Map to hold key value pairs for groceries
	map<string, int> groceryFreq;
	string filePath;

public:
	//Sets file path for backup
	GroceryTracker(){
		filePath = "frequency.dat";
	}
	//sets all inputs to lower for easier validation
	string inputLower(string input){
		string lowerItem;
		//gets length of string
		int n = input.length();

		//iterates through string setting letters to lower case
		for (int i = 0; i < n; i++){
			lowerItem += tolower(input[i]);
		}

		return lowerItem;
	}

	//read file and add to map
	void readInput(const string& filePath){
		ifstream txtFile(filePath);
		string item;

		if (txtFile.is_open()){
			while (getline(txtFile, item)){
				groceryFreq[inputLower(item)]++;
			}
			txtFile.close();
		}
		else {
			cout << "Error: unable to open file at " << filePath << endl;
		}
	}

	//saving the data to the backup
	void saveData(){
		ofstream txtFile(filePath);

		if (txtFile.is_open()){
			for (const auto& pair : groceryFreq) {
				txtFile << pair.first << " " << pair.second << endl;
			}
			txtFile.close();

		}
		else {
			cout << "Error: unable to creat file named " << filePath << endl;
		}
	}

	//Print frequency for option 2
	void printGroceryFreq() {
		for (const auto& pair : groceryFreq) {
			cout << pair.first << " " << pair.second << endl;
		}
	}

	//Print histogram for option 3
	void printGroceryHistogram() {
		for (const auto& pair : groceryFreq) {
			cout << pair.first << " ";
			for (int i = 0; i < pair.second; i++) {
				cout << "*";
			}
			cout << endl;
		}
	}

	//Main menu function
	void MainMenu() {
		int menuOpt;
		string userChoice;

		do {
			//Print Menu
			cout << "***MAIN MENU***" << endl;
			cout << "1) Search Grocery Itme Frequency" << endl;
			cout << "2) Print Grocery Item Frequecny" << endl;
			cout << "3) Print Grocery Item Histogram" << endl;
			cout << "4) Exit Menu" << endl;
			cout << "Please enter a choice." << endl;

			//User input
			cin >> menuOpt;

			//Validate input
			switch (menuOpt) {
			case 1:
				cout << "Please enter the item you would like to look up: ";
				cin.ignore();
				getline(cin, userChoice);
				cout << "Frequency of " << userChoice << " is: " << groceryFreq[inputLower(userChoice)] << endl;
				break;
			case 2:
				printGroceryFreq();
				break;
			case 3:
				printGroceryHistogram();
				break;
			case 4:
				saveData();
				break;
			default:
				cout << "Invalid input. Please try again." << endl;
				break;
			}
		} while (menuOpt != 4);
	}
};

//Main function, calls Menu function
int main() {
	string txtFile = "CS210_Project_Three_Input_File.txt";
	GroceryTracker groceryTracker;

	//reads text file
	groceryTracker.readInput(txtFile);

	//calls menu
	groceryTracker.MainMenu();

}
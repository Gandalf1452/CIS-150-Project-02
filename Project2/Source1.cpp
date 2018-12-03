#include <iostream>
#include <string>
#include <fstream>
#include <vector>


using namespace std;


struct valid_user { 
	int id; 
	string first_name; 
	string last_name; 
	string username; 
	string password;
};

int loginScreen(vector<valid_user>&, int&);
void readUsers(vector<valid_user>&, ifstream&, ofstream&);
void readChart(vector<vector<string>>&, ifstream&);
void displayOptions(vector<valid_user>&, int, int);

int main() {
	ifstream in;
	ofstream out;
	vector<valid_user> users;
	vector<vector<string>> seat;
	int i;
	int choice = 0;
	readUsers(users, in, out);
	i = loginScreen(users, i);
	displayOptions(users, choice, i);
	system("pause");
	return 0;

}

void readUsers(vector<valid_user>& users, ifstream& in, ofstream& out) {
	in.open("systemUser.txt");
	int i = 0;
	//This loop will read each line of the given file until the end of the file is reached
	while (!in.eof()) {
		users.push_back(valid_user());
		in >> users[i].id >> users[i].first_name >> users[i].last_name >> users[i].username >> users[i].password;
		++i;
	}
	in.close();
}

int loginScreen(vector<valid_user>& user, int& i) {
	bool isTrue = false;
	//The function will continuously ask the user for login info until they match a logged username and password
	while (!isTrue) {
		string userInput, passInput;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "                 WELCOME TO AIR TICKET SYSTEM" << endl;
		cout << "-----------------------------------------------------------------" << endl;
		cout << "Please enter your username: ";
		cin >> userInput;
		cout << "Please enter your password: ";
		cin >> passInput;
		//This loop checks all the logged user to see if the info matches with user input
		for (i = 0; i < user.size(); ++i) {
			if (userInput == user[i].username && passInput == user[i].password) {
				isTrue = true;
				return i;
			}
		}
		if (!isTrue) {
			cout << "Invalid username and password, try again" << endl;
		}
	}

}

void readChart(vector<vector<string>>& seat, ifstream& in) {

}

void displayOptions(vector<valid_user>& user, int choice, int i) {
	bool quit = false;
	while (!quit) {
		cout << "----------------------------------------------------" << endl;
		cout << "       WELCOME TO AIR TICKET SYSTEM - " << user[i].first_name << " " << user[i].last_name << endl;
		cout << "----------------------------------------------------" << endl;
		cout << "   1. Display Seat Chart" << endl;
		cout << "   2. Reserve Seat" << endl;
		cout << "   3. Cancel Reservation" << endl;
		cout << "   4. Save Seat Chart to File" << endl;
		cout << "   5. Statistics" << endl;
		cout << "   6. Help" << endl;
		cout << "   7. Quit" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << " Please select an option (1-7): ";
		cin >> choice;
		
	}
	
}
	

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
void readChart(vector<vector<string>>&, vector<vector<string>>&, ifstream&, int, int);
void readChartSize(ifstream&, int&, int&);
void displayChart(vector<vector<string>>&);
void reserveSeat(vector<vector<string>>&, vector<vector<string>>&);
void cancelReserve(vector<vector<string>&>, vector<vector<string>>&);
int displayOptions(vector<valid_user>&, int, int);

int main() {
	ifstream in;
	ofstream out;
	vector<valid_user> users;
	vector<vector<string>> seat;
	vector<vector<string>> seatRef;
	int i;
	int columns = -1, rows = 0, choice = 0;
	bool quit = false;
	readUsers(users, in, out);
	i = loginScreen(users, i);
	readChartSize(in, columns, rows);
	readChart(seat, seatRef, in, columns, rows);
	while (!quit) {
		choice = displayOptions(users, choice, i);
		if (choice == 1) {
			displayChart(seat);
		}
		else if (choice == 2) {
			reserveSeat(seat, seatRef);
		}
		else if (choice == 3) {

		}
		else if (choice == 7) {
			quit = true;
		}
		else {
			cout << "Not a valid choice, type in a valid choice, please" << endl;
		}
	}
	
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

void readChartSize(ifstream& in, int& columns, int& rows) {
	string col = "1", tmp;
	in.open("chartIn.txt");


	//Checks to see if we are still reading from the first row
	while (col[0] == '1') {
		in >> col;

		++columns;
	}
	
	in.close();//Closing and opening the file to reset where the pointer is
	in.open("chartIn.txt");

	//This loop will continue to check each line until there are no lines to read, counting the number of rows
	while (getline(in, tmp)) {
		++rows;
	}
	in.close();
}

void readChart(vector<vector<string>>& seat, vector<vector<string>>& ref, ifstream& in, int columns, int rows) {
	in.open("chartIn.txt");
	seat.resize(rows); //Resizes the rows to the number found from readChartSize
	for (int i = 0; i < seat.size(); ++i) {
		seat[i].resize(columns);//Resizes each row to the number of columns
		for (int j = 0; j < seat[i].size(); ++j) {
			in >> seat[i][j];//Fills each space in the 2-D vector of seats with contents of the file chartIn.txt
		}
	}
	in.close();
	in.open("chartIn.txt");
	ref.resize(rows); //Resizes the rows to the number found from readChartSize
	for (int i = 0; i < ref.size(); ++i) {
		ref[i].resize(columns);//Resizes each row to the number of columns
		for (int j = 0; j < ref[i].size(); ++j) {
			in >> ref[i][j];//Fills each space in the 2-D vector of seat reference with contents of the file chartIn.txt
		}
	}
	in.close();
}

void displayChart(vector<vector<string>>& seat) {
	for (int i = 0; i < seat.size(); ++i) {
		for (int j = 0; j < seat[i].size(); ++j) {
			cout << seat[i][j] << " ";//Prints out each value in the 2-D vector seats
		}
		cout << endl;
	}
}

void reserveSeat(vector<vector<string>>& seat, vector<vector<string>>& ref) {
	string input, row;
	char col;
	int i, j, a, b;
	bool isTaken = false;
	cout << endl << endl << "Ok, what seat are you looking to reserve? ";
	cin >> input;//The program gets the seat the user wants to reserve
	col = toupper(input.back());//The column the user chose is found based on their input
	for (int i = 0; i < input.size() - 1; ++i) {//This loop finds the other values the user inputted, setting them to rows
		row.push_back(input[i]);
	}
	int rowNum = stoi(row);//Stoi converts the string row into an int for later use
	for (i = 0; i < seat.size(); ++i) {//This loop runs through the whole chart to check if the seat the user picked is taken or not
		for (j = 0; j < seat[i].size(); ++j) {
			if (ref[i][j] == input && seat[i][j] == "X") {
				cout << "Sorry, that seat is already reserved, you will have to choose another" << endl;
				isTaken = true;
			}
			else if (ref[i][j] == input && seat[i][j] != "X") {
				a = i;
				b = j;
			}
		}
	}
	if (!isTaken) {//This part will only run if the input the user selected did not result in the seat being already reserved
		//This if-else checks if the user input is outside of the range of the chart
		if (rowNum > seat.size() || int(col) > int((((seat[rowNum-1]).back()).back())) || rowNum < 0 || int(col) < int(((seat[rowNum-1])[0]).back())) {
			cout << "Sorry, that seat is not available on this plane, try choosing another" << endl;
		}
		else {
			cout << "Ok, seat " << seat[a][b] << " is reserved for you." << endl;
			seat[a][b] = "X";
		}
	}
	
	
}

int displayOptions(vector<valid_user>& user, int choice, int i) {
	//This loop will keep on running until the quit option is chosen
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
	return choice;
}
	

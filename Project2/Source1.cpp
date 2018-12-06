#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;


struct valid_user { 
	int id; 
	string first_name; 
	string last_name; 
	string username; 
	string password;
};

int loginScreen(vector<valid_user>&, int&);
void readUsers(vector<valid_user>&, ifstream&);
void readChart(vector<vector<string>>&, vector<vector<string>>&, ifstream&, int, int, string);
void readChartSize(ifstream&, int&, int&, string);
void displayChart(vector<vector<string>>&);
void reserveSeat(vector<vector<string>>&, vector<vector<string>>&);
void cancelReserve(vector<vector<string>>&, vector<vector<string>>&);
void writeChart(vector<vector<string>>&, ofstream&, string&);
void statistics(vector<vector<string>>&, vector<vector<string>>&, ofstream&);
void helpMenu();
int displayOptions(vector<valid_user>&, int, int);

int main() {
	ifstream in;
	ofstream out;
	vector<valid_user> users;
	vector<vector<string>> seat;
	vector<vector<string>> seatRef;
	string fileName = "chartIn.txt";
	int i, columns = -1, rows = 0, choice = 0;
	bool quit = false;
	readUsers(users, in);
	i = loginScreen(users, i);
	readChartSize(in, columns, rows, fileName);
	readChart(seat, seatRef, in, columns, rows, fileName);
	//This loop will keep checking the user's choice until they choose quit
	while (!quit) {
		choice = displayOptions(users, choice, i);
		if (choice == 1) {
			displayChart(seat);
		}
		else if (choice == 2) {
			reserveSeat(seat, seatRef);
		}
		else if (choice == 3) {
			cancelReserve(seat, seatRef);
		}
		else if (choice == 4) {
			writeChart(seat, out, fileName);
		}
		else if (choice == 5) {
			statistics(seat, seatRef, out);
		}
		else if (choice == 6) {
			helpMenu();
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

void readUsers(vector<valid_user>& users, ifstream& in) {
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

void readChartSize(ifstream& in, int& columns, int& rows, string fileName) {
	string col = "1", tmp;
	in.open(fileName);


	//Checks to see if we are still reading from the first row
	while (col[0] == '1') {
		in >> col;

		++columns;
	}
	
	in.close();//Closing and opening the file to reset where the pointer is
	in.open(fileName);

	//This loop will continue to check each line until there are no lines to read, counting the number of rows
	while (getline(in, tmp)) {
		++rows;
	}
	in.close();
}

void readChart(vector<vector<string>>& seat, vector<vector<string>>& ref, ifstream& in, int columns, int rows, string fileName) {
	in.open(fileName);
	seat.resize(rows); //Resizes the rows to the number found from readChartSize
	for (int i = 0; i < seat.size(); ++i) {
		seat[i].resize(columns);//Resizes each row to the number of columns
		for (int j = 0; j < seat[i].size(); ++j) {
			in >> seat[i][j];//Fills each space in the 2-D vector of seats with contents of the chart file
		}
	}
	in.close();
	//The code section below is the same as the one above, except that this is fillin a reference chart to use for reservations
	in.open(fileName);
	ref.resize(rows); 
	for (int i = 0; i < ref.size(); ++i) {
		ref[i].resize(columns);
		for (int j = 0; j < ref[i].size(); ++j) {
			in >> ref[i][j];
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
	input.back() = toupper(input.back());
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

void cancelReserve(vector<vector<string>>& seat, vector<vector<string>>& ref) {
	string input, row;
	char col;
	int i, j, a, b;
	bool isTaken = true;
	cout << endl << endl << "Ok, what seat are you looking to cancel reservation for? ";
	cin >> input;//The program gets the seat the user wants to cancel reservation for
	col = toupper(input.back());//The column the user chose is found based on their input
	for (int i = 0; i < input.size() - 1; ++i) {//This loop finds the other values the user inputted, setting them to rows
		row.push_back(input[i]);
	}
	int rowNum = stoi(row);//Stoi converts the string row into an int for later use
	for (i = 0; i < seat.size(); ++i) {//This loop runs through the whole chart to check if the seat the user picked is reserved or not
		for (j = 0; j < seat[i].size(); ++j) {
			if (ref[i][j] == input && seat[i][j] != "X") {
				cout << "ERROR: Seat not reserved yet, try a seat you have reserved" << endl;
				isTaken = false;
			}
			else if (ref[i][j] == input && seat[i][j] == "X") {
				a = i;
				b = j;
			}
		}
	}
	if (isTaken) {//This part will only run if the input the user selected is already reserved
		//This if-else checks if the user input is outside of the range of the chart
		if (rowNum > ref.size() || int(col) > int((((ref[rowNum - 1]).back()).back())) || rowNum < 0 || int(col) < int(((ref[rowNum - 1])[0]).back())) {
			cout << "Sorry, that seat is not available on this plane, try choosing another" << endl;
		}
		else {
			cout << "Ok, seat " << ref[a][b] << " is taken off the reservation for you." << endl;
			seat[a][b] = ref[a][b];
		}
	}
}

void writeChart(vector<vector<string>>& seat, ofstream& out, string& fileName) {
	cout << "What is the filename you want to write out to? ";
	cin >> fileName;
	out.open(fileName);
	for (int i = 0; i < seat.size(); ++i) {
		for (int j = 0; j < seat[i].size(); ++j) {
			out << seat[i][j] << " ";//Writes out each value in the 2-D vector seats to the output file
		}
		out << endl;
	}
	cout << "File save succeeded!" << endl;
}

void statistics(vector<vector<string>>& seat, vector<vector<string>>& ref, ofstream& out) {
	int availSeatCount = 0, resSeatCount = 0, seatCount = 0;
	float resSeatPerc = 0.0, availSeatPerc = 0.0;
	vector<string> availSeats;
	vector<string> resSeats;
	//This loop will count up the number of available seats and reserved seats
	for (int i = 0; i < seat.size(); ++i) {
		for (int j = 0; j < seat[i].size(); ++j) {
			if (seat[i][j] == "X") {
				++resSeatCount;
				resSeats.push_back(ref[i][j]);
			}
			else {
				++availSeatCount;
				availSeats.push_back(ref[i][j]);
			}
		}
	}
	seatCount = availSeatCount + resSeatCount;//Calculating total seats
	resSeatPerc = (float(resSeatCount) / float(seatCount)) * 100.0;//Calculating percent of seats reserved
	availSeatPerc = (float(availSeatCount) / float(seatCount)) * 100.0;//Calculating percent of seats available
	out.open("statistics.txt");
	//Displaying all the statistics and writing them out to a file
	out << "Number of available seats: " << availSeatCount << endl;
	cout << "Number of available seats: " << availSeatCount << endl;
	out << "Number of reserved seats: " << resSeatCount << endl;
	cout << "Number of reserved seats: " << resSeatCount << endl;
	out << "Percentage of seats available: " << fixed << setprecision(2) << resSeatPerc << "%" << endl;
	cout << "Percentage of seats available: " << fixed << setprecision(2) << resSeatPerc << "%" << endl;
	out << "Percentage of seats reserved: " << fixed << setprecision(2) << availSeatPerc << "%" << endl;
	cout << "Percentage of seats reserved: " << fixed << setprecision(2) << availSeatPerc << "%" << endl;
	out << "Seats available: ";
	cout << "Seats available: ";
	for (int i = 0; i < availSeats.size(); ++i) {
		out << availSeats[i] << " ";
		cout << availSeats[i] << " ";
	}
	out << endl << "Seats reserved: ";
	cout << endl << "Seats reserved: ";
	for (int i = 0; i < resSeats.size(); ++i) {
		out << resSeats[i] << " ";
		cout << resSeats[i] << " ";
	}
	out << endl;
	cout << endl;
}

void helpMenu() {
	cout << endl << "1: Displays the seats in a chart, including the seat already reserved, marked by an X" << endl;
	cout << "2: Prompts an input for a seat to reserve and will reserve it for you if it is available" << endl;
	cout << "3: Cancel a reservation made previously based on input" << endl;
	cout << "4: Saves the chart of seats to a text file named from user input" << endl;
	cout << "5: Shows the number of available seats and reserved seats, percentage of seats available and reserved," << endl;
	cout << "   and shows the seats that are available and reserved" << endl;
	cout << "6: Get more info on each of the options" << endl;
	cout << "7: Exits the program" << endl;
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
	

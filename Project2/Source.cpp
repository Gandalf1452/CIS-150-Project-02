#include <iostream>;
using namespace std;
 /*
 Name: Ryan Hendershot
 Creation Date: 9-21-18
 Modification Date: 9-21-18
 Purpose: Create a square with a character given by user input
 */
int main()
{
	char symbol;
	cout << "Hello and welcome to the square creation using any character!" << endl;


	cout << "Type the character you want to use: ";
	cin >> symbol;	
	
	cout << endl << endl << "Symbol selected: " << symbol << endl << endl;
	cout << symbol << symbol << symbol << endl << symbol << " " << symbol << endl << symbol << symbol << symbol << endl;

	cout << "Thank you for using the square creation tool, goodbye!" << endl;
	system("pause");
		
		return 0;
}

#include "HighScoreManager.h"
#include "User.h"
#include <stdio.h>
#include <string>
#include <iostream>

int main() {
	bool inProgram = true;
	string userName;
	User currentUser;
	HighScoreManager highScores;
	int menuChoice;

	cout << "Welcome to the High Score Manager." << endl;
	cout << "Please enter your username to log in. If your name is not recognised, a new user will be created." << endl;

	getline(cin, userName);

	currentUser = currentUser.login(userName);

	do{
		cout << "Menu: Please choose one of the following options..." << endl << "1) Enter your high score" << endl << "2) Print the top 10 scores" << 
			endl << "3) Edit your information" << endl << "4) Delete your user information" << endl << "5) Exit" << endl;

		cin >> menuChoice;

		while (menuChoice < 1 || menuChoice > 5){
			cout << "Invalid choice. Please choose a number from 1-5." << endl << "1) Enter your high score" << endl << "2) Print the top 10 scores" <<
				endl << "3) Edit your information" << endl << "4) Delete your user information" << endl << "5) Exit" << endl;
			cin >> menuChoice;
		}

		if (menuChoice == 1) {
			//Allow user to update their high score
			currentUser.SetHighScore(userName);
		}
		else if(menuChoice == 2) {
			//Print the top 10 scores from the binary file
			highScores.PrintHighScore();
		}
		else if (menuChoice == 3) {
			//Allow user to edit their information
			currentUser = currentUser.UpdateUser(currentUser);
		}
		else if (menuChoice == 4) {
			//Delete the user and log them out automatically
			currentUser.DeleteUser(currentUser);

			cout << "Your information has been deleted. You will now be logged out..." << endl;
			inProgram = false;
		}
		else {
			//Update the list (this will run and update regardless of if a new user has been added, or a user has edited their information)
			currentUser.UpdateUserList(currentUser);
			inProgram = false;
		}

	}while (inProgram);


	cout << "You are now logged out." << endl << "Thank you for using the High Score Manager." << endl << "Goodbye." << endl;

	system("PAUSE");
	return 0;
}
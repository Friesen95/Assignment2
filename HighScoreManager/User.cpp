#include "User.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

User User::login(string userName){
	bool existingUser = CheckIfUserExists(userName);
	if (existingUser == true) {
		//Check file for match and store user

		cout << "Welcome back, " << userName << endl;
	}
	else{
		//Create user

		cout << "Nice to meet you, " << userName << "! A new account has been created for you!" << endl;
	}
	return User();
}

bool User::CheckIfUserExists(string userName)
{
	string line;
	size_t pos = 0;
	string delimiter = ",";
	//Check list of users stored in users 
	fstream usersFile("Users.txt", ios::in);
	if (usersFile.is_open()) {
		while (getline(usersFile, line))
		{
			pos = line.find(delimiter);
			if((line.substr(0, pos)) == userName) {
				cout << "User found";
				return true;
			}
		}
	}
	else {
		cout << "The file was not found!";
	}
	//Read in first line from users file
	//check name against name
	//if there's a match return true, else false
	return false;
}

void User::UpdateUserList(User user)
{
	int updateMenuChoice, UserInput;
	string userInput;
	do {
		cout << "What would you like to edit?" << endl <<
			"1) First Name" << endl << "2) Last Name" << endl << "3) Age" << endl << "4) Exit";
		cin >> updateMenuChoice;

		if (updateMenuChoice == 1)
		{
			cout << "New First Name: ";
			getline(cin, userInput);
			user.setFirstName(userInput);
		}
		else if (updateMenuChoice == 2)
		{
			cout << "New Last Name: ";
			getline(cin, userInput);
			user.setLastName(userInput);
		}
		else if (updateMenuChoice == 3)
		{
			cout << "New Age: ";
			cin >> UserInput;
			user.setAge(UserInput);
		}
		else if (updateMenuChoice == 4)
		{
			cout << "Thank you" << endl;
		}
		else
		{
			cout << "Invalid Choice" << endl;
		}
	} while (updateMenuChoice < 1 || updateMenuChoice > 4);
	// call the update txt file here
}

void User::DeleteUser(User currentUser)
{
	string line;
	size_t pos = 0;
	string delimiter = ",";
	//Check list of users stored in users 
	fstream usersFile("Users.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempUser.txt");
	if (usersFile.is_open()) {
		while (getline(usersFile, line))
		{
			pos = line.find(delimiter);
			if ((line.substr(0, pos)) != currentUser.username) {
				updateFile << line;
			}
		}
	}
	else {
		cout << "The file was not found!";
	}
	remove("Users.txt");
	rename("tempUser.txt", "Users.txt");
}

int User::SetHighScore()
{
	return 0;
}

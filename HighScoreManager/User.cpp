#include "User.h"
#include "HighScoreManager.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

User User::login(string userName){
	User currentUser;
	bool existingUser = CheckIfUserExists(userName);
	if (existingUser == true) {
		string line;
		size_t pos = 0;
		string delimiter = ",";
		bool keepChecking = true;
		//Check list of users stored in users 
		fstream usersFile("Users.txt", ios::in);
		if (usersFile.is_open()) {
			//While there's another line
			while (getline(usersFile, line) && keepChecking)
			{
				//Grab the first delimiter position (username)
				pos = line.find(delimiter);
				//If they match, set user info
				if ((line.substr(0, pos)) == userName) {
					int section = 1;
					currentUser.setUsername(line.substr(0, pos));
					while ((pos = line.find(delimiter)) != std::string::npos)
					{
						//Based on what section we are at, update the information
						if (section == 2) {
							currentUser.setFirstName(line.substr(0, pos));
						}
						else if (section == 3) {
							currentUser.setLastName(line.substr(0, pos));
						}
						else if (section == 4){
							if (line.substr(0, pos) == ""){
								currentUser.setAge(-1);
							}
							else {
								currentUser.setAge(std::stoi(line.substr(0, pos)));
							}
						}
						section++;
						line.erase(0, pos + delimiter.length());
					}

					keepChecking = false;
				}
			}
		}
		else {
			cout << "The file was not found!";
		}
		cout << "Welcome back, " << currentUser.getUsername() << endl;
	}
	else{
		//Create user
		currentUser.setUsername(userName);
		currentUser.setAge(-1);
		cout << "Nice to meet you, " << currentUser.getUsername() << "! A new account has been created for you!" << endl
			<< "By default, your first & last name as well as your age will not be set." << endl;
	}
	return User(currentUser);
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

User User::UpdateUser(User user)
{
	string menuChoice, userInput;
	int updateMenuChoice;
	do {
		//Prompt the user for what they want to update
		cout << "What would you like to edit?" << endl <<
			"1) First Name" << endl << "2) Last Name" << endl << "3) Age" << endl << "4) Exit" << endl;
		cin >> menuChoice;
		updateMenuChoice = std::stoi(menuChoice);
		//Set the user's information to the new info based on their choice
		if (updateMenuChoice == 1)
		{
			cout << "New First Name: ";
			cin >> userInput;
			user.setFirstName(userInput);
		}
		else if (updateMenuChoice == 2)
		{
			cout << "New Last Name: ";
			cin >> userInput;
			user.setLastName(userInput);
		}
		else if (updateMenuChoice == 3)
		{
			cout << "New Age: ";
			cin >> userInput;
			int newAge = std::stoi(userInput);
			user.setAge(newAge);
		}
		else if (updateMenuChoice == 4)
		{
			cout << "Thank you. Your information has been updated. You will now be returned to the main menu." << endl;
		}
		else
		{
			cout << "Invalid Choice" << endl;
		}
	} while (updateMenuChoice != 4);
	//Return the updated user instance
	return user;
}

void User::DeleteUser(User currentUser)
{
	string line;
	size_t pos = 0;
	string delimiter = ",";
	//Check list of users stored in users 
	fstream usersFile("Users.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempUser.txt", ofstream::out | ofstream::trunc);
	if (usersFile.is_open()) {
		while (getline(usersFile, line))
		{
			pos = line.find(delimiter);
			//If the username is NOT a match, add it to the temp file
			//where it does match, that user will be skipped over
			if ((line.substr(0, pos)) != currentUser.username) {
				updateFile << line << endl;
			}
		}
	}
	else {
		cout << "The file was not found!";
	}
	usersFile.close();
	updateFile.close();
	remove("Users.txt");
	rename("tempUser.txt", "Users.txt");
}

void User::SetHighScore(string userName)
{	
	HighScoreManager highScores;
	int newScore = highScores.CreateHighScore(userName);
	highScores.UpdateHighScore(newScore, userName);
}

void User::UpdateUserList(User currentUser)
{
	string userAge;
	if (currentUser.age == -1)
	{
		userAge = "";
	}
	else {
		userAge = std::to_string(currentUser.getAge());
	}
	bool userFound = false;
	string line;
	size_t pos = 0;
	string delimiter = ",";
	//Check list of users stored in users 
	fstream usersFile("Users.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempUser.txt", ofstream::out | ofstream::trunc);
	if (usersFile.is_open()) {
		while (getline(usersFile, line))
		{
			//If username is a match, update it based on their current settings
			pos = line.find(delimiter);
			if ((line.substr(0, pos)) == (currentUser.getUsername())) {
				updateFile << currentUser.getUsername() << "," << currentUser.getFirstName() << "," <<
					currentUser.getLastName() << "," << userAge << "," << endl;
				userFound = true;
			}
			//If it's not a match, then just add the original line
			else
			{
				updateFile << line << endl;
			}
		}
		//If we found no match for the user, it's a new user, add their info
		if (userFound == false) {
			updateFile << currentUser.getUsername() << "," << currentUser.getFirstName() << "," <<
				currentUser.getLastName() << "," << userAge << "," << endl;
		}
	}
	else {
		cout << "The file was not found!";
	}
	//Close the files, overwrite the old Users file with the temp one holding the updated info
	usersFile.close();
	updateFile.close();
	remove("Users.txt");
	rename("tempUser.txt", "Users.txt");
}

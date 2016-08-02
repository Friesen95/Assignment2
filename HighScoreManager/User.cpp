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
	//Check list of users stored in users 
	fstream usersFile("Users.txt", ios::in);
	if (usersFile.is_open()) {
		while (getline(usersFile, line))
		{

		}
	}
	else {

	}
	//Read in first line from users file
	//check name against name
	//if there's a match return true, else false
	return false;
}

string User::UpdateUserList()
{
	return string();
}

void User::DeleteUser()
{
	
}

int User::SetHighScore()
{
	return 0;
}

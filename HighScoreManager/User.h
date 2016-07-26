#define user_h

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class User {
public:
	User login(string);
	bool CheckIfUserExists(string);
	string UpdateUserList();
	void DeleteUser();
	int SetHighScore();
private:
	struct UserInfo{
		string username;
		int age;
		string firstName;
		string lastName;
	};

};
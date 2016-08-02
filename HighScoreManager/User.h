#define user_h

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class User {
private: string firstName;
		 string lastName;
		 string username;
		 int age;

public: string getUsername() { return username; };
		string getFirstName() { return firstName; };
		void setFirstName(string FirstName) { firstName = FirstName; };
		string getLlastName() { return lastName; };
		void setLastName(string LastName) { lastName = LastName; };
		void setAge(int age) { this->age = age; };
		int getAge() { return age; };
		User login(string);
		bool CheckIfUserExists(string);
		void UpdateUserList(User user);
		void DeleteUser(User currentUser);
		int SetHighScore();



};
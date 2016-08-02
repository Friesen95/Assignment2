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
		void setUsername(string userName) { username = userName; };
		string getFirstName() { return firstName; };
		void setFirstName(string FirstName) { firstName = FirstName; };
		string getLastName() { return lastName; };
		void setLastName(string LastName) { lastName = LastName; };
		void setAge(int age) { this->age = age; };
		int getAge() { return age; };
		User login(string);
		bool CheckIfUserExists(string);
		User UpdateUser(User user);
		void UpdateUserList(User);
		void DeleteUser(User currentUser);
		void SetHighScore(string);
};
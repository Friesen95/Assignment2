#include "HighScoreManager.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
//Got the time function from http://en.cppreference.com/w/cpp/chrono

int HighScoreManager::CreateHighScore(string userName)
{
	string scoreString;
	int highScore;
	cout << "Please enter your new high score, " << userName << " : ";
	cin >> scoreString;
	highScore = std::stoi(scoreString);
	cout << "Your new high score is " << highScore << endl;
	return highScore;
}

void HighScoreManager::UpdateHighScore(int newScore, string userName)
{
	cout << "Updating scores..." << endl;
	std::chrono::time_point<std::chrono::system_clock> time;
	
	bool placeFound = false;
	int points;
	string line;
	size_t pos = 0;
	string delimiter = ",";
	fstream scoresFile("Scores.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempScore.txt", ofstream::out | ofstream::trunc);
	if (scoresFile.is_open()) {
		cout << "Scores file open..." << endl;
		int position = 0;
		while (getline(scoresFile, line))
		{
			cout << "checkin lines...";
			pos = line.find(delimiter);
			for (int x = 1; x <= 3; x++)
			{
				cout <<"Inside for loop" << x;
				// this if statment is incorrect something
				if (x == 2) {
					points = std::stoi(line.substr(0, pos));
					cout << " %$ " << position <<": " << points << endl;
					if (points <= newScore)
					{
						cout << "Adding New Score";
						time = std::chrono::system_clock::now();
						std::time_t _time = std::chrono::system_clock::to_time_t(time);
						updateFile << userName << "," << newScore << "," << std::ctime(&_time) << endl;
						placeFound = true;
					}
				}
				else 
				{
					updateFile << line << endl;
					line.erase(0, pos + delimiter.length());
				}
				
			}
		}
		if (placeFound == false)
		{
			cout << "Adding New Score";
			time = std::chrono::system_clock::now();
			std::time_t _time = std::chrono::system_clock::to_time_t(time);
			updateFile << userName << "," << newScore << "," << std::ctime(&_time) << endl;

		}


	}
	else {
		cout << "The file was not found!";
	}
	scoresFile.close();
	updateFile.close();
	remove("Scores.txt");
	rename("tempScore.txt", "Scores.txt");
	return;
}

void HighScoreManager::PrintHighScore()
{
	int const HIGHSCORE_TOP10 = 10;
	string line;
	size_t pos = 0;
	string delimiter = ",";
	int section;
	fstream usersFile("Scores.txt", ios::in);
	if (usersFile.is_open()) {
		// get the first 10 results 
		cout << "Position" << "\tUsername" << "\t\tScore" << "\t\tDate" << endl;
		int position = 1;
		int nameSize;
		for (int x = 1; x <= HIGHSCORE_TOP10; x++)
		{
			getline(usersFile, line);
			// substring the line 3 times because there are three items
			for (int y = 1; y <= 3; y++)
			{
				pos = line.find(delimiter);
				if (y == 1)
				{
					cout << x << ")\t\t" << line.substr(0, pos);
					nameSize = line.substr(0, pos).length();
				}
				else if (y == 2)
				{
					if (nameSize < 8) {
						cout << "\t\t\t" << line.substr(0, pos);
					}
					else {
						cout << "\t\t" << line.substr(0, pos);
					}
				}
				else
				{
					cout << "\t\t" << line.substr(0, pos);
				}
				line.erase(0, pos + delimiter.length());
			}
			cout << endl;
		}
	}
	else {
		cout << "The file was not found!";
	}
}
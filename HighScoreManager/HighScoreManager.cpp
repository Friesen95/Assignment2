#define _CRT_SECURE_NO_WARNINGS
#include "HighScoreManager.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <ctime>
//Got the time function from http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

int HighScoreManager::CreateHighScore(string userName)
{
	//Prompt user to enter their latest high score, return it
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
	//This function will open the scores file, read through each line, check the line to see if the score
	//is greater than or equal to the one in the line being read - if so, the new score will be inserted - if not,
	//the original line will just be copied
	cout << "Updating scores..." << endl;
	bool placeFound = false;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	int points;
	string line, user;
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
			for (int x = 1; x <= 3; x++)
			{
				pos = line.find(delimiter);
				if (x == 1)
				{
					// assign the user to a string
					user = line.substr(0, pos);
				}
				else if (x == 2)
				{
					points = std::stoi(line.substr(0, pos));
					//cout <<"Points:"<< points << endl;
					if (newScore >= points && placeFound == false)
					{
						//cout << "Adding New Score - true";
						
						updateFile << userName << "," << newScore << "," << (now->tm_year + 1900) 
							<< '/'
							<< (now->tm_mon + 1) << '/'
							<< now->tm_mday << "," << endl;
						placeFound = true;
						updateFile << user << "," << line << endl;
					}
					else
					{
						updateFile << user << "," << line << endl;
					}
				}
				line.erase(0, pos + delimiter.length());
			}
			//cout << endl << "End of for loop";
		}
		if (placeFound == false)
		{
			//cout << "Adding New Score - false";
			updateFile << userName << "," << newScore << "," << (now->tm_year + 1900)
				<< '/'
				<< (now->tm_mon + 1) << '/'
				<< now->tm_mday << "," << endl;
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
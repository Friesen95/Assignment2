#include "HighScoreManager.h"
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>

int HighScoreManager::CreateHighScore(string userName)
{
	string scoreString;
	int highScore;
	cout << "Please enter your new high score, " << userName << " : ";
	getline(cin, scoreString);
	highScore = std::stoi(scoreString);
	return highScore;
}

void HighScoreManager::UpdateHighScore(int newScore, string userName)
{
	string line;
	size_t pos = 0;
	string delimiter = ",";
	//Check list of users stored in users 
	fstream scoresFile("Scores.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempScore.txt", ofstream::out | ofstream::trunc);
	if (scoresFile.is_open()) {
		while (getline(scoresFile, line))
		{
			pos = line.find(delimiter);
			int section = 1;
			while ((pos = line.find(delimiter)) != std::string::npos)
			{
				if (section == 2) {
					cout << line.substr(0, pos);
				}
			}
		}

	}
	else {
		cout << "The file was not found!";
	}
	scoresFile.close();
	updateFile.close();
	remove("Scores.txt");
	rename("tempScore.txt", "Scores.txt");
}

void HighScoreManager::PrintHighScore()
{
}

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
	cin >> scoreString;
	highScore = std::stoi(scoreString);
	cout << "Your new high score is " << highScore << endl;
	return highScore;
}

void HighScoreManager::UpdateHighScore(int newScore, string userName)
{
	cout << "Updating scores..." << endl;
	string line;
	size_t pos = 0;
	string delimiter = ",";
	fstream scoresFile("Scores.txt", ios::in);
	ofstream updateFile;
	updateFile.open("tempScore.txt", ofstream::out | ofstream::trunc);
	if (scoresFile.is_open()) {
		cout << "Scores file open..." << endl;
		while (getline(scoresFile, line))
		{
			cout << "checkin lines...";
			pos = line.find(delimiter);
			int section = 1;
			while ((pos = line.find(delimiter)) != std::string::npos)
			{
				if (section == 2) {
					cout << "2: " << line.substr(0, pos) << endl;
				}
				section++;
				line.erase(0, pos + delimiter.length());
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
		cout << "Position" << "\t\tUsername" << "\t\t Score" << "\t\t Date" << endl;
		int position = 1;
		for(int x = 1; x <= HIGHSCORE_TOP10; x++)
		{
			getline(usersFile, line);
			// substring the line 3 times because there are three items
			for (int y = 1; y <= 3; y++)
			{
				pos = line.find(delimiter);
				if (y == 1)
				{
					cout << x << ")\t\t\t"<< line.substr(0, pos);
				}
				else if (y == 2)
				{
					cout << "\t\t\t" << line.substr(0, pos);
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

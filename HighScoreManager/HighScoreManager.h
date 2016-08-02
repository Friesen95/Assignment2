#define highscoremanager_h

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HighScoreManager {
public:
	int CreateHighScore(string);
	void UpdateHighScore(int, string);
	void PrintHighScore();

	struct UserScore{
		string username;
		int score;
		string date;
	};
};
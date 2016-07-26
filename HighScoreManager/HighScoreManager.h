#define highscoremanager_h

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HighScoreManager {
public:
	void CreateHighScore();
	void UpdateHighScore();
	void PrintHighScore();
	
private:
	struct UserScore{
		string username;
		int score;
		//date
	};
};
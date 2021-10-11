#pragma once
#include<list>
#include<queue>
#include<fstream>
#include<sstream>
#include<string>
#include"SFML/Graphics.hpp"
#include"Gameplay.h"

using namespace sf;
using namespace std;

class High_score
{
public:
	void HighScore(int score);
private:
	void WriteScoreBin(ofstream& out, list<int>& value);
	void WriteScore(ofstream& out, queue<int>& best);
	string readStringBin(short length, ifstream& in);

	friend class Gameplay;
	list<int> bestScores;
	queue<int> chopped;
	bool cannotAcces = false;
	Text warning;
};


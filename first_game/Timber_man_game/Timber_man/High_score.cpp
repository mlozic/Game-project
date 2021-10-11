#include "High_score.h"
#include<iostream>

using namespace std;

void High_score::HighScore(int score)
{
	Gameplay g;
	ifstream in("Best.txt");
	ofstream out("High_score.bin", ios_base::binary);

	if (!in || !out)
	{
		cannotAcces = true;
		warning.setFont(g.font);
		warning.setCharacterSize(10);
		warning.setPosition(300, 20);
		warning.setString("Can't acces file");
		return ;
	}
	
	string line;

	while (getline(in, line))
	{
		stringstream ss(line);
		int temp;
		ss >> temp;
		bestScores.push_back(temp);
	}

	bestScores.push_back(score);
	bestScores.sort();
	
	WriteScoreBin(out, bestScores);

	in.close();
	out.close();

	ifstream bin("High_score.bin", ios_base::binary);
	ofstream bout("Best.txt");
	if (!bin||!bout)
	{
		cannotAcces = true;
		warning.setFont(g.font);
		warning.setCharacterSize(10);
		warning.setPosition(300, 20);
		warning.setString("Can't acces file");
		return;
	}

	while (true)
	{
		short length;
		if (!bin.read((char*)&length, sizeof(length))) {
			break;
		}

		string ranked = readStringBin(length, bin);
		stringstream converter(ranked);
		int temp;
		converter >> temp;
		chopped.push(temp);
	}

	WriteScore(bout, chopped);

	bin.close();
	bout.close();
}

void High_score::WriteScoreBin(ofstream& out, list<int>& values)
{
	auto itend = values.rbegin();
	advance(itend, 10);

	for (auto it = values.rbegin(); it != itend; ++it)
	{
		stringstream isGreater;
		isGreater << *it;
		string onList = isGreater.str();


		short length = onList.length();
		out.write((char*)&length, sizeof(length));
		out.write(onList.c_str(), length);
	}

	bestScores.clear();
}

void High_score::WriteScore(ofstream& out, queue<int>& best)
{
	while (!best.empty())
	{
		out << best.front() << endl;
		best.pop();
	}
}

string High_score::readStringBin(short length, ifstream& in)
{
	char* temp = new char[length];
	in.read(temp, length);
	string s(temp, length);
	delete[] temp;
	
	return s;
}

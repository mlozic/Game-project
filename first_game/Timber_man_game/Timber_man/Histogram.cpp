#include "Histogram.h"
#include<sstream>

using namespace std;

string Histogram::to__string(int time, int score)
{
	string hashstr = "";
	if (score > 0)
	{
		char* hash = new char[score];
		for (unsigned i = 0; i < score; i++)
		{
			hash[i] = '#';
		}
		string numOfHash(hash, score);
		hashstr = numOfHash;
		delete[] hash;
	}

	stringstream pushLog;
	pushLog << time << "-" << time + 1 << "sec: " << score<<" "<<hashstr;

	return pushLog.str();
}

int Histogram::Convert(string& value)
{
	stringstream stacker(value);
	int t;
	stacker >> t;
	return t;
}

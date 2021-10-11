#pragma once
#include<stack>
#include<string>

using namespace std;

class Histogram
{
public:
	string to__string(int time, int score);
private:
	int Convert(string& value);
};
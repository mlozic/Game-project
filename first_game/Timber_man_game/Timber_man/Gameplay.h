#pragma once
#include<vector>
#include<stack>
#include<string>
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"High_score.h"
#include"Histogram.h"

using namespace sf;

const float AXE_POSITION_LEFT = 700;
const float AXE_POSITION_RIGHT = 1075;

class Gameplay
{
public:
	Gameplay();
	Gameplay(RenderWindow* window);
	void Animation();
	void draw();
	bool gamePaused = true;
	bool acceptInput = false;
	bool wannaHighScore = false;
	bool wannaHist = false;
	bool isPPressed = false;
	Sprite spriteAxe;

private:
	friend class High_score;
	friend class Histogram;
	void Action();
	void createHistogram(stack<Text>& histScore);
	void UpdateBranches(int seed);
	void LogMovement();
	void Death();
	void CallHist();

	float gen_rand(int max, int min);
	enum class side { LEFT, RIGHT, NONE };
	
	std::vector <side> branchPosition;
	side playerSide = side::LEFT;
	RenderWindow* window;
	Clock clock;
	Clock clockhist;

	Time dt;
	Time dt02;
	Time gameTime;

	Font font;
	Text histText;
	Text messageText;
	Text gamePausedText;
	Text scoreText;
	Text fpsText;
	Text end;
	Text yesHist;
	Text warningtxt;
	Text timeCounter;
	Text highscoreLines;
	std::vector<Text> linesFromBeast;
	std::vector<Text>drawHist;
	std::stack<string>histScores;

	Sprite spriteRIP;
	Sprite spritePlayer;
	Sprite spriteBackground;
	Sprite spriteTree;
	Sprite spriteBee;
	Sprite spriteLog;;
	std::vector <Sprite> spriteTrees;
	std::vector <Sprite> spriteclouds;
	std::vector <Sprite> spriteBranches;

	Texture textureRIP;
	Texture textureAxe;
	Texture texturePlayer;
	Texture textureBackground;
	Texture textureTree;
	Texture textureTree2;
	Texture textureBee;
	Texture textureClouds;
	Texture textureBranch;
	Texture textureLog;

	SoundBuffer chopBuffer;
	SoundBuffer deathBuffer;
	SoundBuffer outOTBufer;

	Sound chop;
	Sound death;
	Sound outOfTime;

	RectangleShape timeBar;
	RectangleShape rect1;
	RectangleShape rect2;
	RectangleShape rect3;

	long long duration;
	int score = 0;
	int drawn = 0;
	int timer = 1;
	int subScore = 0;

	bool beeActive;
	bool histActive = true;
	bool warning = false;
	bool canWrite = true;
	bool logActive = false;
	bool branchSet = false;
	bool dead = false;
	std::vector <bool> cloudActive;
	
	float beeSpeed;
	float height = 120;
	float width = 200;
	float histTime = 0;
	float histGoal = 1000;
	float heightScnd = 120;
	float heightRd = 120;
	float logSpeedX = 1000;
	float logSpeedY = -1500;
	float timeRemaining = 6.0f;
	float timeBarStartWidth = 400;
	float timeBarHeigth = 80;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
	std::vector <float> cloudSpeed;
};


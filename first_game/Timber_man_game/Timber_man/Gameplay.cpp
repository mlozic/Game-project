#include "Gameplay.h"
#include<ctime>
#include<sstream>
#include<chrono>

using namespace std;
using namespace chrono;

Gameplay::Gameplay()
{
}

Gameplay::Gameplay(RenderWindow* window) : Gameplay()
{
	this->window = window;

	High_score h;
	auto begin = high_resolution_clock::now();
	h.HighScore(score);
	auto endTime = high_resolution_clock::now();

	duration = duration_cast<chrono::milliseconds>(endTime - begin).count();

	chopBuffer.loadFromFile("sound/chop.wav");
	chop.setBuffer(chopBuffer);

	deathBuffer.loadFromFile("sound/death.wav");
	death.setBuffer(deathBuffer);

	outOTBufer.loadFromFile("sound/out_of_time.wav");
	outOfTime.setBuffer(outOTBufer);

	textureBackground.loadFromFile("graphics/background.png");
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	textureTree.loadFromFile("graphics/tree.png");
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	textureTree2.loadFromFile("graphics/tree2.png");
	Sprite tree;
	for (unsigned i = 0; i < 5; i++)
	{
		spriteTrees.push_back(tree);
		spriteTrees[i].setTexture(textureTree2);
	}
	spriteTrees[0].setPosition(20, 0);
	spriteTrees[1].setPosition(300, -100);
	spriteTrees[2].setPosition(1300, -300);
	spriteTrees[3].setPosition(1490, -500);
	spriteTrees[4].setPosition(1750, 0);

	textureBee.loadFromFile("graphics/bee.png");
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);
	beeActive = false;
	beeSpeed = 0.0f;

	textureClouds.loadFromFile("graphics/cloud.png");
	int position = 0;
	Sprite cloud;
	bool cactive = false;
	float cspeed = 0.0f;
	for (unsigned i = 0; i < 6; i++)
	{
		spriteclouds.push_back(cloud);
		spriteclouds[i].setTexture(textureClouds);
		spriteclouds[i].setPosition(0, position);
		cloudActive.push_back(cactive);
		cloudSpeed.push_back(cspeed);
		position += 250;
	}

	font.loadFromFile("fonts/KOMIKAP_.ttf");

	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600, 105));
	rect1.setPosition(0, 30);

	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);

	FloatRect textRect = messageText.getLocalBounds();

	messageText.setCharacterSize(75);
	messageText.setFillColor(Color::White);
	messageText.setFont(font);
	messageText.setOrigin(textRect.left + (textRect.width / 2.0f),
		textRect.top + (textRect.height / 2.0f));
	messageText.setPosition(960 / 2.0f, 1000 / 2.0f);
	messageText.setString("Press Enter to Start! \n Press h for high score list");

	highscoreLines.setFont(font);
	highscoreLines.setFillColor(Color::White);
	highscoreLines.setCharacterSize(75);
	
	timeCounter.setFont(font);
	timeCounter.setCharacterSize(30);
	timeCounter.setFillColor(Color::White);
	timeCounter.setPosition(650, 50);

	end.setFont(font);
	end.setCharacterSize(50);
	end.setPosition(450, 300);
	end.setFillColor(Color::White);
	end.setString("Press Enter to chop again \n    ESC to leave");
	
	yesHist.setFont(font);
	end.setCharacterSize(40);
	end.setPosition(700, 600);
	end.setFillColor(Color::White);
	end.setString("wanna histogram? \n press y");

	


	warningtxt.setFont(font);
	warningtxt.setCharacterSize(15);
	warningtxt.setPosition(600, 20);
	warningtxt.setFillColor(Color::White);
	warningtxt.setString("Can't acces file");

	scoreText.setCharacterSize(100);
	scoreText.setFillColor(Color::White);
	scoreText.setFont(font);
	scoreText.setPosition(20, 20);

	fpsText.setFont(font);
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(100);
	fpsText.setPosition(1200, 20);

	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeigth));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition(760, 1000);

	textureBranch.loadFromFile("graphics/branch.png");
	Sprite branch;
	side bposition = side::NONE;
	for (unsigned i = 0; i < 4; i++)
	{
		spriteBranches.push_back(branch);
		spriteBranches[i].setTexture(textureBranch);
		spriteBranches[i].setPosition(-2000, -2000);
		spriteBranches[i].setOrigin(220, 200);
		branchPosition.push_back(bposition);
	}

	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600, 105));
	rect1.setPosition(0, 30);

	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);

	rect3.setFillColor(sf::Color(0, 0, 0, 150));
	rect3.setSize(Vector2f(2500, 1050));
	rect3.setPosition(0, 30);

	texturePlayer.loadFromFile("graphics/player.png");
	playerSide = side::LEFT;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	textureRIP.loadFromFile("graphics/rip.png");
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(875, 360);

	textureAxe.loadFromFile("graphics/axe.png");
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	textureLog.loadFromFile("graphics/log.png");
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);


}
float Gameplay::gen_rand(int max, int min)
{
	return rand() % (max - min + 1) + min;
}

void Gameplay::Animation()
{
	dt = clock.restart();
	float movement = beeSpeed * dt.asSeconds();
	srand(time(nullptr));

	if (acceptInput)
	{
		Action();
	}

	if (logActive)
	{
		LogMovement();
	}

	if (!beeActive)
	{
		beeSpeed = gen_rand(400, 150);
		float height = gen_rand(1000, 500);
		spriteBee.setPosition(2000, height);
		beeActive = true;
	}

	else
	{
		spriteBee.setPosition(spriteBee.getPosition().x - movement, spriteBee.getPosition().y);
	}

	if (spriteBee.getPosition().x < -100)
	{
		beeActive = false;
	}

	for (unsigned i = 0; i < 3; i++)
	{
		if (!cloudActive[i])
		{
			cloudSpeed[i] = gen_rand(150, 100);
			float height = gen_rand(150, 100);
			spriteclouds[i].setPosition(-200, height);
			cloudActive[i] = true;
		}
		else
		{

			spriteclouds[i].setPosition(spriteclouds[i].getPosition().x + (cloudSpeed[i] * dt.asSeconds()),
				spriteclouds[i].getPosition().y);
		}
		if (spriteclouds[i].getPosition().x > 1920)
		{
			cloudActive[i] = false;
		}
	}

	for (unsigned i = 0; i < 4; i++)
	{
		float height = i * 225;
		if (branchPosition[i] == side::LEFT)
		{
			spriteBranches[i].setPosition(610, height);
			spriteBranches[i].setRotation(180);
		}
		else if (branchPosition[i] == side::RIGHT)
		{
			spriteBranches[i].setPosition(1330, height);
			spriteBranches[i].setRotation(0);
		}
		else
		{
			spriteBranches[i].setPosition(3000, height);
		}
	}

	

	timeRemaining -= dt.asSeconds();
	timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeigth));

	if (timeRemaining <= 0.0f)
	{
		if (canWrite)
		{
			High_score h;
			
			h.HighScore(score);
			
			canWrite = false;
		}
		gamePaused = true;

		outOfTime.play();
		messageText.setPosition(660, 450);
		messageText.setString("Out of Time! :(");
		messageText.setFillColor(Color::Red);
		messageText.setCharacterSize(120);
	}

	if (branchPosition[3] == playerSide)
	{
		Death();
	}
}

void Gameplay::UpdateBranches(int seed)
{
	for (unsigned j = 4 - 1; j > 0; j--) {
		branchPosition[j] = branchPosition[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branchPosition[0] = side::LEFT;
		break;

	case 1:
		branchPosition[0] = side::RIGHT;
		break;

	default:
		branchPosition[0] = side::NONE;
		break;
	}
}

void Gameplay::Action()
{
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		playerSide = side::RIGHT;
		score++;
		subScore++;
		timeRemaining += (2 / score) + .15;
		chop.play();

		if (timeRemaining > 6.0f)
		{
			timeRemaining = 6.0f;
		}

		spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
		spritePlayer.setPosition(1200, 720);
		spritePlayer.setTextureRect(sf::IntRect(0, 0, 150, 192));

		UpdateBranches(score);

		spriteLog.setPosition(810, 720);
		logSpeedX = -5000;
		logActive = true;

		acceptInput = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		playerSide = side::LEFT;
		score++;
		subScore++;
		timeRemaining += (2 / score) + .15;
		chop.play();

		if (timeRemaining > 6.0f)
		{
			timeRemaining = 6.0f;
		}

		spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
		spritePlayer.setPosition(580, 720);


		UpdateBranches(score);

		spriteLog.setPosition(810, 720);
		logSpeedX = 5000;
		logActive = true;

		acceptInput = false;
	}
}

void Gameplay::createHistogram(stack<Text>& histScore)
{
	Histogram h;
	
}

void Gameplay::Death()
{
	gamePaused = true;
	acceptInput = false;
	death.play();
	if (canWrite)
	{
		High_score h;
		h.HighScore(score);
		canWrite = false;
	}

	if (playerSide == side::LEFT)
	{
		spriteRIP.setPosition(525, 760);
	}

	else
	{
		spriteRIP.setPosition(1200, 720);
	}
	spriteAxe.setPosition(-300, -300);
	spritePlayer.setPosition(-300, -300);
	messageText.setString("ALIVE'NT");
	messageText.setFillColor(Color::Red);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1000 / 2.0f);

	dead = true;
}

void Gameplay::CallHist()
{
}



void Gameplay::LogMovement()
{
	spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
		spriteLog.getPosition().y + (logSpeedX * dt.asSeconds()));

	if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
	{
		logActive = false;
		spriteLog.setPosition(810, 720);
	}
}


void Gameplay::draw()
{
	High_score h;
	Histogram his;
	dt02 = clockhist.getElapsedTime();
	float timerhist = dt02.asSeconds();

	window->draw(spriteBackground);


	for (unsigned i = 0; i < 5; i++)
	{
		window->draw(spriteTrees[i]);
	}
	window->draw(spriteclouds[0]);
	window->draw(spriteclouds[1]);
	window->draw(spriteclouds[2]);
	for (unsigned i = 0; i < 4; i++)
	{
		window->draw(spriteBranches[i]);
	}

	window->draw(spriteTree);

	if (playerSide == side::LEFT)
	{
		spritePlayer.setTextureRect(sf::IntRect(150, 0, -150, 192));
	}

	else
	{
		spritePlayer.setTextureRect(sf::IntRect(0, 0, 150, 192));
	}

	window->draw(spritePlayer);
	window->draw(spriteAxe);
	window->draw(spriteLog);
	window->draw(rect1);
	window->draw(rect2);
	window->draw(spriteBee);

	if (wannaHighScore && !dead && timeRemaining > 0.0f)
	{
		stringstream durationTime;
		durationTime << "it took:\n " << duration << "ms, to get data from file";
		timeCounter.setString(durationTime.str());

		ifstream in("Best.txt");
		if (!in)
		{
			window->draw(warningtxt);
			in.close();
		}
		string line;
		int row = 1;
		while (getline(in, line))
		{
			if (row>5)
			{
				stringstream lineReader;
				lineReader << "No" << row << ". " << line << " logs";
				highscoreLines.setString(lineReader.str());
				highscoreLines.setPosition(950, heightScnd);
				linesFromBeast.push_back(highscoreLines);
				heightScnd += 150;
				row++;
			}
			else
			{
				stringstream lineReader;
				lineReader << "No" << row << ". " << line << " logs";
				highscoreLines.setString(lineReader.str());
				highscoreLines.setPosition(250, height);
				linesFromBeast.push_back(highscoreLines);
				height += 150;
				row++;
			}
		}
		row = 1;
			
		in.close();

		for (unsigned k = 0; k < 10; k++)
		{
			window->draw(linesFromBeast[k]);
		}
		
		messageText.setCharacterSize(55);
		messageText.setString("Press N \n to leave \n high scores");
		messageText.setPosition(1550, 400);
		
		window->draw(timeCounter);
	

		if (Keyboard::isKeyPressed(Keyboard::N))
		{
			messageText.setCharacterSize(75);
			messageText.setString("Press Enter to Start! \n Press h for high score list");
			messageText.setPosition(960 / 2.0f, 1000 / 2.0f);
			wannaHighScore = false;
			height = 120;
			heightScnd = 120;
		}

	}

	if (h.cannotAcces)
	{
		window->draw(h.warning);
	}
	drawn++;
	if (drawn==100)
	{
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());

		std::stringstream ss2;
		ss2 << "FPS = " << 1 / dt.asSeconds();
		fpsText.setString(ss2.str());

		drawn = 0;
	}

	window->draw(scoreText);
	window->draw(fpsText);
	window->draw(timeBar);

	if (!histActive)
	{
		clockhist.restart();
	}

	if (timerhist>=timer)
	{
		histScores.push(his.to__string(timer, subScore));
		subScore = 0;
		timer++;
	}

	if (gamePaused)
	{
		


		if (timeRemaining>0.0f && !dead && isPPressed)
		{
			messageText.setPosition(660, 450);
			messageText.setString("Press Enter to continue");
			messageText.setFillColor(Color::White);
			messageText.setCharacterSize(50);
		}

		window->draw(messageText);
		if (timeRemaining <= 0.0f)
		{
			histActive = false;
			window->draw(end);
			window->draw(yesHist);

			if (wannaHist)
			{
				timer = 0;
				yesHist.setPosition(-300, -300);
				end.setPosition(-300, -300);
				window->draw(rect3);
				while (!histScores.empty()) {

					histText.setFont(font);
					histText.setCharacterSize(15);
					histText.setFillColor(Color::White);

					if (height>=1110)
					{
						height = 120;

						width += 450;
					}

					histText.setPosition(width, heightRd);
					histText.setString(histScores.top());
					
					drawHist.push_back(histText);

					heightRd += 45;

					histScores.pop();
				}

				for (unsigned i = 0; i < drawHist.size(); i++)
				{
					window->draw(drawHist[i]);
				}
				Text messageTextHist;
				messageTextHist.setFont(font);
				messageTextHist.setCharacterSize(55);
				messageTextHist.setString("Press B");
				messageTextHist.setPosition(1550, 1000);
				messageTextHist.setFillColor(Color::White);
					
				window->draw(messageTextHist);

				if (Keyboard::isKeyPressed(Keyboard::B))
				{
					end.setPosition(450, 300);
					end.setPosition(700, 600);
					wannaHist = false;
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				timeRemaining = 6.0f;
				score = 0;
				isPPressed = false;
				histActive = true;
			}
		}

		if (dead)
		{
			histActive = false;
			window->draw(spriteRIP);
			window->draw(end);
			window->draw(yesHist);

			if (wannaHist)
			{
				timer = 1;
				yesHist.setPosition(-300, -300);
				end.setPosition(-300, -300);
				window->draw(rect3);
				while (!histScores.empty()) {

					histText.setFont(font);
					histText.setCharacterSize(15);
					histText.setFillColor(Color::White);

					if (height >= 1110)
					{
						height = 120;

						width += 450;
					}

					histText.setPosition(width, heightRd);
					histText.setString(histScores.top());

					drawHist.push_back(histText);

					heightRd += 45;

					histScores.pop();
				}

				for (unsigned i = 0; i < drawHist.size(); i++)
				{
					window->draw(drawHist[i]);
				}
				Text messageTextHist;
				messageTextHist.setFont(font);
				messageTextHist.setCharacterSize(55);
				messageTextHist.setString("Press B");
				messageTextHist.setPosition(1550, 1000);
				messageTextHist.setFillColor(Color::White);

				window->draw(messageTextHist);

				if (Keyboard::isKeyPressed(Keyboard::B))
				{
					end.setPosition(450, 300);
					end.setPosition(700, 600);
					wannaHist = false;
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Return)) {
				gamePaused = false;
				acceptInput = true;
				canWrite = true;
				histActive = true;
				isPPressed = false;
				dead = false;
				for (unsigned i = 0; i < 4; i++)
				{
					branchPosition[i] = side::NONE;
				}
				if (playerSide==side::LEFT)
				{
					spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
					spritePlayer.setPosition(580, 720);
				}
				else
				{
					spriteAxe.setPosition(AXE_POSITION_RIGHT, 830);
					spritePlayer.setPosition(1200, 720);
				}
				timeRemaining = 6.0f;
				score = 0;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			histActive = true;
			isPPressed = false;
		}
	}
}

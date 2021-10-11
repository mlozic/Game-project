#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Gameplay.h"

using namespace sf;

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber Man", Style::Fullscreen);
	Gameplay timberMan(&window);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::KeyReleased && !timberMan.gamePaused) {
					timberMan.acceptInput = true;
					timberMan.spriteAxe.setPosition(2000,
					timberMan.spriteAxe.getPosition().y);
				}
			}


			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			
			if (Keyboard::isKeyPressed(Keyboard::H))
			{
				timberMan.wannaHighScore = true;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Y))
			{
				timberMan.wannaHist = true;
			}

			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				timberMan.gamePaused = false;
			}

			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				timberMan.isPPressed = true;
				timberMan.gamePaused=true;
			}

			if (!timberMan.gamePaused)
			{
				timberMan.Animation();
			}


			window.clear();
			timberMan.draw();
			window.display();
		}

	return 0;
}
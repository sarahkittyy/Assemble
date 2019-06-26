#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(500, 500), "Assemble")
{
}

int Application::run()
{
	// Game loop
	while (mWindow.isOpen())
	{
		// Poll events.
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				mWindow.close();
				break;

			default:
				break;
			}
		}

		// Clear the window
		mWindow.clear();
		// Draw

		// Flip
		mWindow.display();
	}
}
#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(500, 500), "Assemble"),
	  mSM(&mWindow, &mResource, new States::Game())
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

		// Update the state machine.
		mSM.update();
	}

	return 0;
}
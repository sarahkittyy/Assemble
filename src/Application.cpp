#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(800, 600), "Assemble"),
	  mSM(&mWindow, &mResource, new States::Game())
{
	ImGui::SFML::Init(mWindow);
}

int Application::run()
{
	sf::Clock appClock;

	// Game loop
	while (mWindow.isOpen())
	{
		// Poll events.
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			// Process ImGui events.
			ImGui::SFML::ProcessEvent(event);
			switch (event.type)
			{
			case sf::Event::Closed:
				mWindow.close();
				break;

			default:
				break;
			}
		}
		// Update ImGui.
		ImGui::SFML::Update(mWindow, appClock.restart());

		// Update the state machine.
		mSM.update();
	}

	return 0;
}
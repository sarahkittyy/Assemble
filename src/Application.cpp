#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(800, 600), "Assemble"),
	  mSM(&mWindow, &mResource, new States::Game())
{
	// Load and set icon.
	sf::Image icon;
	icon.loadFromFile("resource/icon.png");
	mWindow.setIcon(32, 32, icon.getPixelsPtr());

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
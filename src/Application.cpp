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
			// Special window events
			switch (event.type)
			{
			case sf::Event::Closed:
				mWindow.close();
				break;

			case sf::Event::Resized:
				mWindow.setSize(event.size.width, event.size.height);
				break;

			default:
				break;
			}
			// Pass all events to the current state.
			mSM.onEvent(event);
		}
		// Update ImGui.
		ImGui::SFML::Update(mWindow, appClock.restart());

		// Update the state machine.
		mSM.update();

		// End the ImGui Update.
		ImGui::EndFrame();
	}

	return 0;
}
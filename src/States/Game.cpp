#include "States/Game.hpp"

namespace States
{

void Game::init()
{
	// Load the background
	mBackgroundTexture = *resource()
							  .texture("resource/env/water.png");
	mBackgroundTexture.setRepeated(true);
	mBackground.setTexture(&mBackgroundTexture);
	sf::Vector2i windowSize = sf::Vector2i(window().getSize());
	mBackground.setSize(sf::Vector2f(windowSize));
	mBackground.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
}

void Game::onEvent(const sf::Event& event)
{
}

void Game::update()
{
	// Set GUI for button / state retrieval.
	drawGUI();
	// Updates

	// Begin Drawing
	window().clear();
	window().draw(mBackground);   // Draw the background first


	ImGui::SFML::Render(window());
	window().display();
}

void Game::drawGUI()
{
}

}
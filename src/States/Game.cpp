#include "States/Game.hpp"

namespace States
{

void Game::init()
{
}

void Game::update()
{
	// Set GUI for button / state retrieval.
	drawGUI();
	// Updates


	// Begin Drawing
	window().clear();

	ImGui::SFML::Render(window());
	window().display();
}

void Game::drawGUI()
{
}

}
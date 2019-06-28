#include "States/Game.hpp"

namespace States
{

void Game::init()
{
	map.reset(new Graphics::Tilemap(&resource(), "resource/maps/map.json"));
	map->autoTile();
}

void Game::update()
{
	// Set GUI for button / state retrieval.
	drawGUI();
	// Updates


	// Begin Drawing
	window().clear();
	window().draw(*map);

	ImGui::SFML::Render(window());
	window().display();
}

void Game::drawGUI()
{
}

}
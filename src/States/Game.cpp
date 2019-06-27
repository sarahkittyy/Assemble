#include "States/Game.hpp"

namespace States
{

void Game::init()
{
}

void Game::update()
{
	window().clear(sf::Color(127, 127, 255));

	window().display();
}

}
#pragma once

#include "Graphics/Tilemap.hpp"
#include "States/State.hpp"
#include "Util/MouseFreelook.hpp"

namespace States
{

/**
 * @brief Main game state.
 * 
 */
class Game : public State
{
public:
	void init();

	void update();

	void onEvent(const sf::Event& event);

private:
	void drawGUI();

	/// The game background.
	sf::RectangleShape mBackground;
	/// Held out of the ResourceManager so we can use setRepeated() safely.
	sf::Texture mBackgroundTexture;
};

}
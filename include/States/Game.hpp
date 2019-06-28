#pragma once

#include "Graphics/Tilemap.hpp"
#include "States/State.hpp"

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

private:
	void drawGUI();

	std::shared_ptr<Graphics::Tilemap> map;
};

}
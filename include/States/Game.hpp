#pragma once

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
};

}
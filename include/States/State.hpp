#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include "ResourceManager.hpp"

namespace States
{

class Machine;

/**
 * @brief Abstract state class.
 * 
 */
class State
{
public:
	/**
	 * @brief Init non-environment-dependent variables.
	 * Do not use window() or resource() as those are intiialized
	 * inside init()
	 * 
	 */
	State();

	/**
	 * @brief Virtual destructor
	 * 
	 */
	virtual ~State();

	/**
	 * @brief Called by the state machine on initialization.
	 * 
	 */
	virtual void init();

	/**
	 * @brief Called once a frame. Draw to window() here.
	 * 
	 */
	virtual void update();

protected:
	/**
	 * @brief For derived states, to use the environment window.
	 * 
	 * @return sf::RenderWindow& The program's window.
	 */
	sf::RenderWindow& window();

	/**
	 * @brief For derived states to have access to a global resource manager.
	 * 
	 * @return ResourceManager& The program resource manager. 
	 */
	ResourceManager& resource();

	/**
	 * @brief Queues for the state machine to change state.
	 * For safety, the state isn't changed until update() has finished running.
	 * 
	 * @param new_state The new state to change to. 
	 */
	void changeState(State* new_state);

private:
	friend class Machine;   // For configuration.

	/// Pointer to the app window
	sf::RenderWindow* mWindow;
	/// Pointer to the resource manager
	ResourceManager* mResource;
	/// Function pointer to change the app machine's state.
	std::function<void(State*)> mChangeState;
};

}
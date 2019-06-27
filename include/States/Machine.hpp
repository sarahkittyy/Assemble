#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>

#include "ResourceManager.hpp"
#include "States/State.hpp"

namespace States
{

/**
 * @brief Manages state instances, and allows for the updating
 * and changing of states.
 * 
 */
class Machine
{
public:
	/**
	 * @brief Initialize the state machine.
	 * 
	 * @param window The app window
	 * @param resource The app resource manager
	 * @param initial The initial state to load.
	 */
	Machine(sf::RenderWindow* window,
			ResourceManager* resource,
			State* initial);

	/**
	 * @brief Change the state of the machine.
	 * For pointer safety, queues the change for the end of the state.update() method.
	 * 
	 * @param new_state The new state to change to.
	 */
	void changeState(State* new_state);

	/**
	 * @brief Updates the current state.
	 * 
	 */
	void update();

	/**
	 * @brief Pass an SFML window event onto the current app state.
	 * 
	 * @param event The event to process.
	 */
	void onEvent(const sf::Event& event);

private:
	/// App window
	sf::RenderWindow* mWindow;
	/// App resource manager
	ResourceManager* mResource;
	/// Active machine state.
	std::shared_ptr<State> mState;
	/// Temporarily holds the next state on changeState(), nullptr if
	/// no change was queued.
	State* mNextState;
	/**
	 * @brief Forces a state change, ignoring whether or not the current state is ready to be deleted.
	 * 
	 * @param new_state The new machine state.
	 */
	void mChangeState(State* new_state);
};

}
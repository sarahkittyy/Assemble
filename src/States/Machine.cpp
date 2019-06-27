#include "States/Machine.hpp"

namespace States
{

Machine::Machine(sf::RenderWindow* window,
				 ResourceManager* resource,
				 State* initial)
	: mWindow(window),
	  mResource(resource)
{
	mChangeState(initial);
}

void Machine::changeState(State* new_state)
{
	// Queue the state change until after update() has finished.
	mNextState = new_state;
}

void Machine::mChangeState(State* new_state)
{
	// Reset mNextState as any queued changes are lost on state change.
	mNextState = nullptr;

	mState.reset(new_state);
	//* State private member configuration.
	mState->mWindow = mWindow;
	mState->mResource = mResource;
	mState->mChangeState = std::bind(&Machine::changeState,
									 this,
									 std::placeholders::_1);

	mState->init();
}

void Machine::update()
{
	mState->update();
	// Update the state if necessary.
	if (mNextState)
	{
		mChangeState(mNextState);
	}
}

void Machine::onEvent(const sf::Event& event)
{
	mState->onEvent(event);
}

}
#include "States/State.hpp"

namespace States
{

State::State()
{
}

State::~State()
{
}

void State::init()
{
}

void State::update()
{
	window().clear();
	window().display();
}

void State::onEvent(const sf::Event& event)
{
}

sf::RenderWindow& State::window()
{
	return *mWindow;
}

ResourceManager& State::resource()
{
	return *mResource;
}

void State::changeState(State* new_state)
{
	mChangeState(new_state);
}

}
#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Main app class
 * 
 */
class Application
{
public:
	/**
	 * @brief Init the app
	 * 
	 */
	Application();

	/**
	 * @brief Run the app
	 * 
	 * @return int The program's exit code
	 */
	int run();

private:
	/// The app window.
	sf::RenderWindow mWindow;
};
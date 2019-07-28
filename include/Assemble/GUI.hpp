#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

namespace Assemble
{

/**
 * @brief Allows streamlined manipulation of the main gui panels
 * 
 */
class GUI
{
public:
	/**
	 * @brief Initialize the three gui panels.
	 * 
	 */
	GUI();

	/**
	 * @brief Resize the window.
	 * 
	 * @param newSize The window's new size.
	 * 
	 */
	void setWindowSize(sf::Vector2u newSize);

	/**
	 * @brief Attempt to start drawing to the right panel.
	 * Returns false if the panel was already written to this frame.
	 * 
	 * @param title The panel's title. If empty, panel is given no title.
	 */
	bool beginRight(std::string title = "");

	/**
	 * @brief Attempt to start drawing to the bottom panel.
	 * Returns false if the panel was already written to this frame.
	 * 
	 * @param title The panel's title. If empty, panel isn't given a title.
	 */
	bool beginBottom(std::string title = "");

	/**
	 * @brief End whatever window was currently being drawn to.
	 * 
	 */
	void end();

	/**
	 * @brief Call in place of ImGui::SFML::Render().
	 * 
	 * @param window The window to render to.
	 */
	void render(sf::RenderWindow& window);

private:
	/// Flags to only allow one write to each panel.
	bool mWroteToRight;
	bool mWroteToBottom;

	// The window size.
	sf::Vector2u mWindowSize;

	/**
	 * @brief Open the right panel, irrelevant of write protection.
	 * 
	 * @param title The panel title.
	 */
	void mBeginRight(std::string title);

	/**
	 * @brief Open the bottom panel, irrelevant of write protection.
	 * 
	 * @param title The panel title.
	 */
	void mBeginBottom(std::string title);
};

}
#include "Assemble/GUI.hpp"

namespace Assemble
{

GUI::GUI()
	: mWroteToRight(false),
	  mWroteToBottom(false),
	  mWindowSize({800, 600})
{
}

void GUI::setWindowSize(sf::Vector2u newSize)
{
	mWindowSize = newSize;
}

bool GUI::beginRight(std::string title)
{
	// Write protection.
	if (mWroteToRight)
	{
		return false;
	}
	mWroteToRight = true;

	mBeginRight(title);
	return true;
}

void GUI::mBeginRight(std::string title)
{
	// WindowFlags
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize;

	// Title bar check.
	if (title.empty())
	{
		flags |= ImGuiWindowFlags_NoTitleBar;
		title = " ";   // For imgui's happiness
	}

	// Unique panel identifier.
	title += "###right";

	// Begin the window.
	ImGui::SetNextWindowPos(ImVec2(mWindowSize.x - 100, 0));
	ImGui::SetNextWindowSize(ImVec2(100, mWindowSize.y - 100));
	ImGui::Begin(title.c_str(), nullptr, flags);
}

bool GUI::beginBottom(std::string title)
{
	// Write protection.
	if (mWroteToBottom)
	{
		return false;
	}
	mWroteToBottom = true;

	mBeginBottom(title);
	return true;
}

void GUI::mBeginBottom(std::string title)
{
	// WindowFlags
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize;

	// Title bar check.
	if (title.empty())
	{
		flags |= ImGuiWindowFlags_NoTitleBar;
		title = " ";   // For imgui's happiness
	}

	// Panel identifier.
	title += "###bottom";

	// Begin the window.
	ImGui::SetNextWindowPos(ImVec2(0, mWindowSize.y - 100));
	ImGui::SetNextWindowSize(ImVec2(mWindowSize.x, 100));
	ImGui::Begin(title.c_str(), nullptr, flags);
}

void GUI::end()
{
	ImGui::End();
}

void GUI::render(sf::RenderWindow& window)
{
	// If the panels weren't written to, create blank panels.
	if (!mWroteToBottom)
	{
		mBeginBottom("");
		end();
	}
	if (!mWroteToRight)
	{
		mBeginRight("");
		end();
	}
	// Unset write-protect flags.
	mWroteToRight = false;
	mWroteToBottom = false;
	ImGui::SFML::Render(window);
}

}
#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <limits>
#include <vector>

#include <iostream>

namespace Util
{

/**
 * @brief Allows for the grouping and selection / deselection
 * of sf::Transformable objects, for panning / zooming with the mouse.
 * 
 */
class MouseFreelook
{
public:
	/**
	 * @brief Initialize the engine
	 * 
	 */
	MouseFreelook();

	/**
	 * @brief Unlock the engine, enabling mouse controls.
	 * 
	 */
	void select();

	/**
	 * @brief Lock the engine, stopping mouse controls.
	 * 
	 */
	void deselect();

	/**
	 * @brief Attach a transformable object to the engine.
	 * 
	 * @param obj The object to attach.
	 */
	void attach(sf::Transformable* obj);

	/**
	 * @brief Removes an object from the engine.
	 * 
	 * @param obj The object to remove.
	 */
	void remove(sf::Transformable* obj);

	/**
	 * @brief Reset all transforms to default.
	 * 
	 */
	void reset();

	/**
	 * @brief Call every time the mouse moves
	 * 
	 * @param x Mouse x distance moved.
	 * @param y Mouse y distance moved.
	 */
	void onMouseMove(float x, float y);

	/**
	 * @brief Calld when the mouse is scrolled.
	 * 
	 * @param delta The change in mouse wheel position.
	 */
	void onMouseScroll(float delta);

private:
	/// Initialized to infinity.
	const float INF;
	/// All contained transformables controlled by the mouse
	std::vector<sf::Transformable*> mObjects;
	/// Tracks position shift applied, and allows for reversing on reset()
	sf::Vector2f mPosShift;
	/// True if the current group of objcts is selected.
	bool mSelected;
	/// Last recorded mouse position, for smooth movement.
	sf::Vector2f mLastMousePos;
	/// Mapping a value from one range to another.
	constexpr float map(float value,
						float low,
						float high,
						float newlow,
						float newhigh);
};

}
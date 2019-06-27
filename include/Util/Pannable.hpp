#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{

/**
 * @brief Contains an sf::Transformable, and updates it with the current mouse position / state, to simulate panning of the object.
 *
 * @tparam An sf::Transformable or equivalent
 */
template <class T>
class Pannable
{
public:
	/**
	 * @brief Init the pannable object.
	 * 
	 * @param window The main program window to pan the object in.
	 * @param args The args to pass to T's constructor.
	 */
	template <typename... Args>
	Pannable(sf::RenderWindow* window,
			 Args&&... args)
		: mItem(args...),
		  mWindow(window),
		  mPanning(false),
		  mPanScale(1)
	{
	}

	/**
	 * @brief Sets the panning scale. When this is higher, less mouse movement will result in more object movement. The inverse is also true.
	 * 
	 * @param scale The new panning scale. 
	 */
	void setPanScale(float scale)
	{
		mPanScale = scale;
	}

	/**
	 * @brief Retrieve the contained object.
	 * 
	 * @return T& Reference to the contained object.
	 */
	T& get()
	{
		return mItem;
	}

	/**
	 * @brief Updates object panning. Call once per frame.
	 * 
	 */
	void update()
	{
		// If we're panning...
		if (mPanning)
		{
			// Get the diff between current mouse & start mouse
			sf::Vector2f mouse_offset = sf::Vector2f(mousePos() - mPanStartPos);
			// Move the contained transformable.
			mObject.setPosition(mObjStartPos + mouse_offset * mPanScale);
		}
	}

	void startPanning()
	{
		mPanning = true;
		mPanStartPos = mousePos();
		mObjectStartPos = mObject.getPosition();
	}

	void stopPanning()
	{
		mPanning = false;
	}

private:
	/// The contained object.
	T mObject;
	/// The program window.
	sf::RenderWindow* mWindow;
	/// Whether or not we are panning
	bool mPanning;
	/// The position we started panning from.
	sf::Vector2i mPanStartPos;
	/// The position of the object when we started panning.
	sf::Vector2f mObjStartPos;
	/// The scale of movement from mouse offset -> object offset.
	float mPanScale;

	/**
	 * @brief Get the current position of the mouse.
	 * 
	 * @return sf::Vector2i The current mouse pos.
	 */
	sf::Vector2i mousePos()
	{
		return sf::Mouse::getPosition(*mWindow);
	}
};

}
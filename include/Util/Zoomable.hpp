#pragma once

#include <SFML/Graphics.hpp>

namespace Util
{

/**
 * @brief Contains an sf::Transformable and allows for zooming it in and out.
 * 
 * @tparam T sf::Transformable compatible.
 */
template <class T>
class Zoomable
{
public:
	/**
	 * @brief Init the zoomable object.
	 * 
	 * @param args The arguments to pass onto T's constructor. 
	 */
	template <typename... Args>
	Zoomable(Args&&... args)
		: mObject(args...),
		  mCurrentZoom(1),
		  mZoomStep(0.1f)
	{
	}

	/**
	 * @brief Get the contained object.
	 * 
	 * @return T& Ref to the object contained inside.
	 */
	T& get()
	{
		return mObject;
	}

	/**
	 * @brief Set the zoom increment/decrement for each zoomIn/Out call.
	 * 
	 * @param new_step The new zoom step.
	 */
	void setZoomStep(float new_step)
	{
		mZoomStep = new_step;
	}

	/**
	 * @brief Get the current zoom step.
	 * 
	 */
	float getZoomStep()
	{
		return mZoomStep;
	}

	/**
	 * @brief Zoom in, by the zoom step.
	 * 
	 */
	void zoomIn()
	{
		mCurrentZoom += mZoomStep;
		mObject.setScale(mCurrentZoom, mCurrentZoom);
	}

	/**
	 * @brief Zoom out by the zoom step.
	 * 
	 */
	void zoomOut()
	{
		mCurrentZoom -= mZoomStep;
		if (mCurrentZoom <= 0.1f)
		{
			mCurrentZoom = 0.1f;
		}
		mObject.setScale(mCurrentZoom, mCurrentZoom);
	}

private:
	/// The conatined object to zoom in and out
	T mObject;
	/// The object's current zoom.
	float mCurrentZoom;
	/// The step for each increment of in/out zoom.
	float mZoomStep;
};

}
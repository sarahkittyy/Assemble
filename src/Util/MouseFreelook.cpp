#include "Util/MouseFreelook.hpp"

namespace Util
{

MouseFreelook::MouseFreelook()
	: INF(std::numeric_limits<float>::infinity()),
	  mSelected(false),
	  mLastMousePos(INF, 0)
{
}

void MouseFreelook::select()
{
	mSelected = true;
}

void MouseFreelook::deselect()
{
	mSelected = false;
	// Mark the mouse position to be re-tracked after deselecting.
	mLastMousePos.x = INF;
}

void MouseFreelook::attach(sf::Transformable* obj)
{
	mObjects.push_back(obj);
}

void MouseFreelook::remove(sf::Transformable* obj)
{
	// Find the element to remove.
	auto found = std::find(mObjects.begin(), mObjects.end(), obj);
	// Exit if not found.
	if (found == mObjects.end())
	{
		return;
	}
	// Otherwise, erase it.
	mObjects.erase(found);
}

void MouseFreelook::reset()
{
}

void MouseFreelook::onMouseMove(float x, float y)
{
	if (!mSelected)
	{
		return;
	}
	// Track the mouse position if it's never been recorded before.
	if (mLastMousePos.x == INF)
	{
		mLastMousePos = {x, y};
		return;
	}

	float dx, dy;
	dx = x - mLastMousePos.x;
	dy = y - mLastMousePos.y;

	// Transform each transformable.
	std::for_each(mObjects.begin(),
				  mObjects.end(),
				  [dx, dy](sf::Transformable*& obj) -> void {
					  obj->move(dx, dy);
				  });

	// Save the new mouse pos.
	mLastMousePos = {x, y};
}

void MouseFreelook::onMouseScroll(float delta)
{
	if (!mSelected)
	{
		return;
	}

	// Transform all transformables
	std::for_each(mObjects.begin(), mObjects.end(),
				  [delta](sf::Transformable*& obj) -> void {
					  if (delta == -1)
					  {
						  obj->setScale(
							  std::max(obj->getScale().x - 0.1f, 0.1f),
							  std::max(obj->getScale().y - 0.1f, 0.1f));
					  }
					  else if (delta == 1)
					  {
						  obj->setScale(
							  std::min(obj->getScale().x + 0.1f, 4.f),
							  std::min(obj->getScale().y + 0.1f, 4.f));
					  }
				  });
}

constexpr float MouseFreelook::map(float value,
								   float low,
								   float high,
								   float newlow,
								   float newhigh)
{
	return ((value - low) / (high - low) * newhigh) + newlow;
}

}
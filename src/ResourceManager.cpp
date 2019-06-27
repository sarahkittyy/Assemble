#include "ResourceManager.hpp"

sf::Texture* ResourceManager::texture(std::string path)
{
	// Try to find the texture.
	auto found = mTextures.find(path);
	if (found == mTextures.end())   // Create it if it doesn't exist.
	{
		mTextures[path].loadFromFile(path);
	}

	return &mTextures[path];
}
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

nlohmann::json* ResourceManager::json(std::string path)
{
	// Try to find the json
	auto found = mJSON.find(path);
	if (found == mJSON.end())
	{
		// Load the json from the file.
		std::ifstream file(path);
		if (!file)
		{
			throw std::runtime_error("Could not open file " + path);
		}
		file >> mJSON[path];
		file.close();
	}

	return &mJSON[path];
}
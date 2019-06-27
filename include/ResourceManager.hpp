#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

/**
 * @brief Manages resources such that only one instance
 * of an expensive resource is loaded at a time.
 * 
 */
class ResourceManager
{
public:
	/**
	 * @brief Load the texutre at the given path.
	 * 
	 * @param path The path to the texture.
	 * @return sf::Texture* The texture.
	 */
	sf::Texture* texture(std::string path);

private:
	/// Mapping of paths to the textures at that path.
	std::unordered_map<std::string, sf::Texture> mTextures;
};
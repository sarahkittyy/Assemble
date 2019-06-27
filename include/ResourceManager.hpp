#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"

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

	/**
	 * @brief Get the json data of a given file.
	 * 
	 * @param path The path to the file.
	 * @return nlohmann::json* The json data inside that file.
	 */
	nlohmann::json* json(std::string path);

private:
	/// Mapping of paths to the textures at that path.
	std::unordered_map<std::string, sf::Texture> mTextures;
	/// Mapping of paths to the json data inside those files.
	std::unordered_map<std::string, nlohmann::json> mJSON;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <string>
#include "ResourceManager.hpp"
#include "nlohmann/json.hpp"

namespace Graphics
{

/**
 * @brief A graphical tilemap, loaded from a json file
 * generated by Tiled
 * 
 */
class Tilemap : public sf::Drawable, public sf::Transformable
{
public:
	/**
	 * @brief Properties of the tilemap.
	 *
	 */
	struct Properties
	{
		/// The map tile size, in pixels.
		sf::Vector2i tileSize;
		/// The map grid size, in tiles.
		sf::Vector2i gridSize;
		/// The size of the texture, in pixels.
		sf::Vector2i texSize;
		/// The size of the texture tilemap grid, in tiles.
		inline const sf::Vector2i texGridSize() const
		{
			return sf::Vector2i(texSize.x / tileSize.x,
								texSize.y / tileSize.y);
		}
	};

	/**
	 * @brief Init the tilemap
	 * 
	 * @param resource The app resource manager
	 */
	Tilemap(ResourceManager* resource);

	/**
	 * @brief Init the tilemap.
	 * 
	 * @param resource The app resource manager.
	 * @param file The JSON file generated by Tiled.
	 */
	Tilemap(ResourceManager* resource,
			std::string file);

	/**
	 * @brief Init the map from the given file.
	 * 
	 * @param file The file to load from
	 */
	void loadFromFile(std::string file);

	/**
	 * @brief Assumes that the tilemap is configured such that the
	 * index that the tile appears in corresponds to the value you get by 
	 * bitmasking the neighboring tiles
	 * 
	 * @remarks Neighbors are bitmasked as such:
	 * -   1   -
	 * 2   -   4
	 * -   8   -
	 * (unsigned char bitmask)
	 * 
	 * When a bit is set, that means that there *is* a tile there.
	 */
	void autoTile();
	
	/**
	 * @brief Converts the window-relative mouse position
	 * into the position of the tile the mouse is on.
	 * 
	 * @param window The window the mouse is relative to.
	 * 
	 * @return sf::Vector2i The pos of the tile the mouse is over. 
	 */
	sf::Vector2i getMousePosition(sf::RenderWindow* window);

	/**
	 * @brief Get the ID of a tile at a given position. 
	 * 
	 * @param pos The tile position.
	 * 
	 * @return int The ID of the tile, -1 if out of bounds.
	 */
	int getTileID(int pos);

	/**
	 * @brief Get the ID of a tile at a given position.
	 * 
	 * @param x The x position
	 * @param y The y position
	 * @return int The ID of the tile, -1 if out of bounds.
	 */
	int getTileID(int x, int y);

private:
	/// SFML draw() override.
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	/// The app resource manager.
	ResourceManager* mResource;

	/// The map vertex array.
	sf::VertexArray mVertices;
	/// Reset and configure the vertex array with mTiles
	void loadVertices();
	/// The map texture
	sf::Texture* mTexture;
	/// The map properties json.
	nlohmann::json mTileProps;

	/// Vector of integers representing the tiles on the map.
	std::vector<int> mTiles;

	/// The map properties
	Properties mProps;
};

}
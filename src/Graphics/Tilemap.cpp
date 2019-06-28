#include "Graphics/Tilemap.hpp"

namespace Graphics
{

Tilemap::Tilemap(ResourceManager* resource)
	: mResource(resource)
{
	mVertices.setPrimitiveType(sf::Quads);
}

Tilemap::Tilemap(ResourceManager* resource,
				 std::string file)
	: mResource(resource)
{
	mVertices.setPrimitiveType(sf::Quads);
	loadFromFile(file);
}

void Tilemap::loadFromFile(std::string file)
{
	namespace fs = std::filesystem;
	using nlohmann::json;

	// Get the file json data.
	json data = *mResource->json(file);
	// Calculate the map properties file name
	std::string props_file = file;
	size_t ext_pos = props_file.find(".json");
	props_file.insert(ext_pos, ".props");
	// Save the map tile extra properties
	mTileProps = *mResource->json(props_file);

	// Get the map properties.
	mProps.gridSize.x = data.at("height").get<int>();
	mProps.gridSize.y = data.at("width").get<int>();
	mProps.tileSize.x = data.at("tilewidth").get<int>();
	mProps.tileSize.y = data.at("tileheight").get<int>();

	// Get the texture.
	fs::path mappath(file);
	mappath = mappath.parent_path();
	std::string img_path = data.at("tilesets")[0].at("image").get<std::string>();
	fs::path rpath = mappath.relative_path() / img_path;
	mTexture = mResource->texture(rpath);
	// Texture props
	mProps.texSize = sf::Vector2i(mTexture->getSize());

	// Init the tiles from the map
	mTiles = data.at("layers")[0].at("data").get<std::vector<int>>();
	loadVertices();
}

void Tilemap::loadVertices()
{
	mVertices.clear();
	// Iterate over all tiles, appending them to the vertex array.
	for (size_t i = 0; i < mTiles.size(); ++i)
	{
		int id = mTiles[i];
		if (id == 0)   // Ignore air tiles
		{
			continue;
		}
		// Decrement the ID, so that the first tile is 0.
		id--;

		sf::Vector2i map_pos;
		map_pos.x = (i % mProps.gridSize.x) * mProps.tileSize.x;
		map_pos.y = (i / mProps.gridSize.x) * mProps.tileSize.y;
		sf::Vector2i tex_pos;
		tex_pos.x = (id % mProps.texGridSize().x) * mProps.tileSize.x;
		tex_pos.y = (id / mProps.texGridSize().y) * mProps.tileSize.y;

		// Append the four quad vertices
		mVertices.append(sf::Vertex(
			sf::Vector2f(map_pos),
			sf::Vector2f(tex_pos)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(map_pos.x + mProps.tileSize.x, map_pos.y),
			sf::Vector2f(tex_pos.x + mProps.tileSize.x, tex_pos.y)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(map_pos + mProps.tileSize),
			sf::Vector2f(tex_pos + mProps.tileSize)));
		mVertices.append(sf::Vertex(
			sf::Vector2f(map_pos.x, map_pos.y + mProps.tileSize.y),
			sf::Vector2f(tex_pos.x, tex_pos.y + mProps.tileSize.y)));
	}
}

int Tilemap::getTileID(int pos)
{
	if (pos < 0 || pos >= mTiles.size())
	{
		return -1;
	}
	return mTiles[pos];
}

int Tilemap::getTileID(int x, int y)
{
	int pos = x + y * mProps.gridSize.x;
	if (pos < 0 || pos >= mTiles.size())
	{
		return -1;
	}
	return mTiles[x + y * mProps.gridSize.x];
}

sf::Vector2i Tilemap::getMousePosition(sf::RenderWindow* window)
{
	// Get the mouse pos.
	sf::Vector2f mouse_pos = (sf::Vector2f)sf::Mouse::getPosition(*window);

	// Transform the mouse position so it's in-line with the
	// map's current transform.
	mouse_pos = getInverseTransform().transformPoint(mouse_pos);

	// Cast the mouse pos into tilemap coords.
	sf::Vector2i map_coords = {
		mouse_pos.x / mProps.tileSize.x,
		mouse_pos.y / mProps.tileSize.y
	};
	
	// Return the coordinates
	return map_coords;
}

void Tilemap::autoTile()
{
	// Append all new bitmasked tiles here.
	std::vector<int> newTiles;
	// Iterate over all tiles.
	for (size_t i = 0; i < mTiles.size(); ++i)
	{
		// Get the X and Y position of the tile.
		int x = i % mProps.gridSize.x;
		int y = i / mProps.gridSize.x;

		// If the tile itself isn't solid (ID < 1), ignore.
		if (int id = getTileID(x, y); id < 1)
		{
			newTiles.push_back(id);
			continue;
		}

		// Get all neighboring tiles.
		// - 0 -
		// 1 - 2
		// - 3 -
		// -------
		int neighbors[4] = {
			getTileID(x, y - 1),
			getTileID(x - 1, y),
			getTileID(x + 1, y),
			getTileID(x, y + 1)};

		// Bitmask all solid neighbors (ID >= 1)
		unsigned char solid_neighbors = 0;
		for (int n = 0; n < 4; ++n)
		{
			if (neighbors[n] >= 1)
			{
				solid_neighbors |= (1 << n);
			}
		}

		// Load the new tile ID into the new tiles vector.
		newTiles.push_back(solid_neighbors + 1);
	}
	// Load the finished tiles.
	mTiles = newTiles;
	loadVertices();
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = mTexture;
	target.draw(mVertices, states);
}
}
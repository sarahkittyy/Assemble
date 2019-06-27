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
	// Clear vertices
	mVertices.clear();

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

	// Iterate over all tiles.
	mTiles = data.at("layers")[0].at("data").get<std::vector<int>>();
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

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = mTexture;
	target.draw(mVertices, states);
}

}
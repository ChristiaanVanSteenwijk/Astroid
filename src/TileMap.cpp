#include "TileMap.hpp"
/*
TileMap::TileMap(std::string filename, sf::Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height)
    :Visibility(filename)
{
    //ctor
    // load the tileset texture
    if(_image.loadFromFile(filename) == false)
    {
        _filename = "";
        _isLoaded =  false;
    }
    else
    {
        _filename = filename;
        _isLoaded =  true;
    }

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (_image.getSize().x / tileSize.x);
            int tv = tileNumber / (_image.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
}

TileMap::~TileMap()
{
    //dtor
}
void TileMap::Draw(sf::RenderWindow& renderWindow)
{
    renderWindow.draw(_vertices);//, _states);
}

sf::Rect<float> TileMap::GetBoundingRect() const
{
    if (_isLoaded)
        return _vertices.getBounds();
}
*/

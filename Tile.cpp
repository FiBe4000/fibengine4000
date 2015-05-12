#include "Tile.h"
#include "GameEngine.h"
#include <iostream>

Tile::Tile()
{
    IsAccessible = false;
    imNumber = 1;
}

Tile::Tile(int num, bool isAccessible, std::string fName, sf::Vector2u tileSetSize)
{
	fileName = fName;
    IsAccessible = isAccessible;
    
    int top = 0;
    int left = (num % tileSetSize.x) * GameEngine::TILE_WIDTH;
    
    while(num >= (top * (tileSetSize.x)))
    {
    	top++;
    }
    top -= 1;
	top *= GameEngine::TILE_HEIGHT;
	
    rect = sf::Rect<int>(left, top, GameEngine::TILE_WIDTH, GameEngine::TILE_HEIGHT);
}

Tile::~Tile()
{
}

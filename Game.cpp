#include "Game.h"
#include "GameEngine.h"

Game::Game() : tilegrid("data/levels/a")
{
    std::cerr << "Game created" << std::endl;
}

Game::~Game()
{
}

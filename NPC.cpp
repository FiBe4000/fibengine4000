#include "NPC.h"
#include "GameEngine.h"

NPC::NPC(float x, float y, std::string id, float stress) : Character("gfx/npcSet.png")
{
	std::cerr << "NPC created" << std::endl;
    
    LoadNpcFile();
    
    direction = LEFT;
    xSpeed = 2;
    ySpeed = 2;
    maxDistX = 100;
    maxDistY = 100;
    width = 13;
    height = 18;
    this->stress = stress;
    
    lastDir = direction;
    Waiting = false;
    
    spawnPosition.x = x;
    spawnPosition.y = y;
    SetX(x);
    SetY(y);
    
    this->id = "npc" + id;
}

NPC::~NPC()
{
}

void NPC::SetX(float newX)
{
	position.x = newX;
	updatePosition();
}

void NPC::SetY(float newY)
{
	position.y = newY;
	updatePosition();
}

void NPC::moveNPCDown(bool CanMove)
{
	moveDown(CanMove, ySpeed);
}

void NPC::moveNPCUp(bool CanMove)
{
	moveUp(CanMove, ySpeed);
}

void NPC::moveNPCRight(bool CanMove)
{
	moveRight(CanMove, xSpeed);
}

void NPC::moveNPCLeft(bool CanMove)
{
	moveLeft(CanMove, xSpeed);
}

void NPC::AI(bool CanMove[])
{	
	mode.Update();
	
	time(&randTime);
	srand((unsigned int) (randTime * ((atoi(id.substr(3, id.length()).c_str())) + randTime)));
	direction = rand() % (LEFT - UP + 1) + UP;
	
	if(direction != lastDir)
	{
		if(walkingClock.getElapsedTime().asSeconds() >= stress)
		{
			Waiting = false;
		}
		else
		{
			Waiting = true;
		}
	}
	
	if(!Waiting)
	{
		if(direction == UP && position.y >= spawnPosition.y - (maxDistY * GameEngine::TILE_HEIGHT))
		{
			moveNPCUp(CanMove[UP]);
		}
		else if(direction == RIGHT && position.x <= spawnPosition.x + (maxDistX * GameEngine::TILE_WIDTH))
		{
			moveNPCRight(CanMove[RIGHT]);
		}
		else if(direction == DOWN && position.y <= spawnPosition.y + (maxDistY * GameEngine::TILE_HEIGHT))
		{
			moveNPCDown(CanMove[DOWN]);
		}
		else if(direction == LEFT && position.x >= spawnPosition.x - (maxDistX * GameEngine::TILE_WIDTH))
		{
			moveNPCLeft(CanMove[LEFT]);
		}
		
		walkingClock.restart();
	}
	
	lastDir = direction;
}

void NPC::LoadNpcFile()
{
}


#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "Character.h"
#include "AIManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>

class NPC : public Character
{
private:
	AIManager mode;
	
    int direction;
	int lastDir;
	int width;
	int height;
	
    float xSpeed;
    float ySpeed;
    float maxDistX;
    float maxDistY;
	float stress;
	
	bool Waiting;
	bool CanSpeak;
	
	time_t randTime;
	
	sf::Vector2f spawnPosition;
	sf::Clock walkingClock;
	
	std::string id;
public:
    NPC(float x, float y, std::string id, float stress);
    virtual ~NPC();

    const float GetX() const { return position.x; }
	const float GetY() const { return position.y; }
	
	float GetXSpeed();
	float GetYSpeed();
	
	const int GetWidth() { return width; }
	const int GetHeight() { return height; }
	
	const std::string GetId() { return id; }
		
    void SetX(float newX);
    void SetY(float newY);

    void Death() { /*PlayerStats.DecreaseLives()*/; }
	void AI(bool CanMove[]);
	void LoadNpcFile();
	
   	void moveNPCDown(bool CanMove);
    void moveNPCUp(bool CanMove);
	void moveNPCRight(bool CanMove);
    void moveNPCLeft(bool CanMove);
};

#endif // NPC_H_INCLUDED

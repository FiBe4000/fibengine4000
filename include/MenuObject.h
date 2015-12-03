#ifndef MENUOBJECT_H_INCLUDED
#define MENUOBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "ActionType.h"

class MenuObject
{
private:

protected:
	float x;
	float y;
	sf::Color color;

public:
	MenuObject();
	virtual ~MenuObject();
	
	virtual sf::FloatRect getSizeRect() {;}
	virtual sf::Vector2f getPosition() {;}
	virtual sf::Color getColor() {;}
	
	virtual ActionType activate() { return NO_ACTION; }
	
	virtual void setColor(sf::Color color) {;}
	virtual void setPosition(float x, float y) { this->x = x; this->y = y; }
	virtual void draw() {;}
};

#endif //MENUOBJECT_H_INCLUDED

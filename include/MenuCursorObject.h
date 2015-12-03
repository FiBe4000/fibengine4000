#ifndef MENUCURSOROBJECT_H_INCLUDED
#define MENUCURSOROBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "MenuObject.h"
#include <ActionType.h>

class MenuCursorObject : public MenuObject
{
private:
	static const float offset = 7.5f;
	sf::Texture bgTex;
	sf::Sprite imSprite;
	sf::Color color;
	
public:
	MenuCursorObject(std::string imPath);
	virtual ~MenuCursorObject();
	
	sf::FloatRect getSizeRect() { return imSprite.getLocalBounds(); }
	sf::Vector2f getPosition() { return imSprite.getPosition(); }
	sf::Color getColor() { return imSprite.getColor(); }
	
	void setSizeFromObject(sf::FloatRect objSize);
	void setPosition(sf::Vector2f pos);
	void setColor(sf::Color color);
	ActionType activate() { return NO_ACTION; }
	void draw();
};

#endif //MENUCURSOROBJECT_H_INCLUDED

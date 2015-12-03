#ifndef ACTIONTEXTOBJECT_H_INCLUDED
#define ACTIONTEXTOBJECT_H_INCLUDED

#include "MenuObject.h"
#include "ActionType.h"
#include <iostream>

class ActionTextObject : public MenuObject
{
private:
	ActionType action;
	sf::Text text;
	sf::Font font;
	sf::Texture bgTex;
	sf::Sprite bgSprite;
	std::string scriptPath;
	int size;
	
public:
	ActionTextObject(ActionType action);
	ActionTextObject(ActionType action, std::string scriptPath, std::string text, std::string fontPath, float x, float y, sf::Color color, int size);
	virtual ~ActionTextObject();
	
	sf::FloatRect getSizeRect() { return bgSprite.getGlobalBounds(); }
	sf::Vector2f getPosition() { return bgSprite.getPosition(); }
	sf::Color getColor() { return text.getColor(); }
	
	ActionType activate();
	
	void setPosition(float x, float y);
	void setColor(sf::Color color);
	void setFont(std::string fontPath);
	void setText(std::string text);
	void setSize(int size);
	void setBgImage(std::string imPath);
	void background(bool status);
	void draw();
};

#endif //ACTIONTEXTOBJECT_H_INCLUDED


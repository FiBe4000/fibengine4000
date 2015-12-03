#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "ActionType.h"
#include "Direction.h"
#include "MenuObject.h"
#include "MenuCursorObject.h"

class Menu
{
private:
    int currentObj;
    
    bool ColorHighlight;
    
    std::vector<MenuObject*> menuObjects;
	
	MenuCursorObject cursor;
	
	sf::Sprite renderingSprite;
	sf::Sprite bgSprite;
	sf::Sprite buttonRowSprite;
	
	sf::Texture bgTexture;
	sf::Texture buttonRowTex;
	sf::Font font;
	sf::Color highlightColor;
	
	ActionType action;
	
	void scaleButtonRow();
	void alignButtons();
	
public:
	Menu();
	Menu(std::string bgPath);
	virtual ~Menu();
	
	ActionType getAction();

	void addObject(MenuObject* obj);
	void addButtonRowBg(std::string imPath, sf::Vector2f pos);
	void moveCursor(Direction dir);
	void setColorHighlight(bool state, sf::Color color);
	void activate();
	void render();
};

#endif //MENU_H_INCLUDED

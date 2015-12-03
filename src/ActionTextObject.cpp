#include "ActionTextObject.h"
#include "GameEngine.h"

ActionTextObject::ActionTextObject(ActionType action)
{
	this->action = action;
	std::cout << action << std::endl;
}

ActionTextObject::ActionTextObject(ActionType action, std::string scriptPath, std::string text, std::string fontPath, float x, float y, sf::Color color, int size)
{
	if(!font.loadFromFile(fontPath))
	{
		//Engine::stop();
	}
	
	this->action = action;
	this->text.setString(text);
	this->text.setFont(font);
	this->text.setPosition(x, y);
	this->text.setCharacterSize(size);
	this->text.setColor(color);
	this->scriptPath = scriptPath;
	setBgImage("gfx/buttonBg.png");
}

ActionTextObject::~ActionTextObject()
{
}

void ActionTextObject::setPosition(float x, float y)
{
	int offset = 20;
	this->text.setPosition(x, y);
	bgSprite.setPosition(text.getPosition().x-(offset/2), text.getPosition().y+(text.getLocalBounds().height/2.75f)-(offset/2));
}

void ActionTextObject::setColor(sf::Color color)
{
	this->text.setColor(color);
}

void ActionTextObject::setFont(std::string fontPath)
{
	if(!font.loadFromFile(fontPath))
	{
		//Engine::stop();
	}
	text.setFont(font);
}

void ActionTextObject::setText(std::string text)
{
	this->text.setString(text);
}

void ActionTextObject::setSize(int size)
{
	this->text.setCharacterSize(size);
}

void ActionTextObject::setBgImage(std::string imPath)
{
	int offset = 20;
	
	if(!bgTex.loadFromFile(imPath))
	{
		//Engine::stop();
	}
	bgSprite.setTexture(bgTex);
	bgSprite.setScale((text.getLocalBounds().width+offset)/bgSprite.getLocalBounds().width, (text.getLocalBounds().height+offset)/bgSprite.getLocalBounds().height);
	bgSprite.setPosition(text.getPosition().x-(offset/2), text.getPosition().y+(text.getLocalBounds().height/2.75f)-(offset/2));
}

void ActionTextObject::background(bool visible)
{
	if(visible)
	{
		bgSprite.setColor(sf::Color(0,0,0,255));
	}
	else
	{
		bgSprite.setColor(sf::Color(0,0,0,0));
	}
}

ActionType ActionTextObject::activate()
{
	if(action == SCRIPT)
	{
		char path[150];
		
		for(int i=0; i<scriptPath.length(); i++)
		{
			path[i] = scriptPath.at(i);
		}
		path[scriptPath.length()] = '\0';
		system(path);
		return SCRIPT;
	}
	else if(action == EXIT)
	{
		std::cout << "EXIT" << std::endl;
		return EXIT;
	}
	else if(START_GAME)
	{
		std::cout << "START" << std::endl;
		return START_GAME;
	}
}

void ActionTextObject::draw()
{
	GameEngine::gEngine.FrameTexture.draw(bgSprite);
	GameEngine::gEngine.FrameTexture.draw(text);
}


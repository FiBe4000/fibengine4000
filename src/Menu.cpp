#include "Menu.h"
#include "GameEngine.h"

Menu::Menu() : cursor("gfx/buttonHighlighter.png")
{
	if(!bgTexture.loadFromFile("gfx/bg.png"))
	{
		//Engine::stop();
	}
	bgSprite.setTexture(bgTexture);
	
	currentObj = -1;
	ColorHighlight = false;
}

Menu::Menu(std::string bgPath) : cursor("gfx/buttonHighlighter.png")
{
	if(!bgTexture.loadFromFile(bgPath))
	{
		//Engine::stop();
	}
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(GameEngine::gEngine.FrameTexture.getSize().x/bgSprite.getLocalBounds().width, GameEngine::gEngine.FrameTexture.getSize().y/bgSprite.getLocalBounds().height);
	
	currentObj = -1;
	ColorHighlight = false;
}

Menu::~Menu()
{
}

void Menu::scaleButtonRow()
{
	int height = 0;
	int offset;
	
	for(int i=0; i<menuObjects.size(); i++)
	{
		if(menuObjects.at(i)->getSizeRect().height > height)
		{
			height = menuObjects.at(i)->getSizeRect().height;
		}
	}
	
	offset = height/2;
	buttonRowSprite.setScale(GameEngine::gEngine.FrameTexture.getSize().x/buttonRowSprite.getLocalBounds().width, (height + offset)/buttonRowSprite.getLocalBounds().height);
}

void Menu::alignButtons()
{
	int numberOfButtons = menuObjects.size();
	
	if(numberOfButtons != 0)
	{
		float buttonSpace = (float)GameEngine::gEngine.FrameTexture.getSize().x / (float)numberOfButtons;
	
		std::cout << "nrButtons: " << numberOfButtons << std::endl << "buttonSpace: " << buttonSpace << std::endl;
	
		for(int i=0; i<numberOfButtons; i++)
		{
			float xPos = ((i+1)*buttonSpace)-(buttonSpace/2)-(menuObjects.at(i)->getSizeRect().width/2);
			float yPos = (buttonRowSprite.getPosition().y + (buttonRowSprite.getGlobalBounds().height/2)) - (menuObjects.at(i)->getSizeRect().height/2.0f);
			std::cout << "xPos: " << xPos << std::endl << "yPos: " << yPos << std::endl << "ButtonWidth: " << menuObjects.at(i)->getSizeRect().width << std::endl;
			menuObjects.at(i)->setPosition(xPos, yPos);
		}
	}
}

void Menu::addObject(MenuObject* obj)
{
	menuObjects.push_back(obj);
	currentObj = 0;
	cursor.setSizeFromObject(menuObjects.at(currentObj)->getSizeRect());
	
	scaleButtonRow();
	alignButtons();
	cursor.setPosition(menuObjects.at(currentObj)->getPosition());
}

void Menu::addButtonRowBg(std::string imPath, sf::Vector2f pos)
{
	if(!buttonRowTex.loadFromFile(imPath))
	{
		//Engine::stop();
	}
	buttonRowSprite.setTexture(buttonRowTex);
	
	scaleButtonRow();
	buttonRowSprite.setPosition(pos);
	alignButtons();
}

void Menu::moveCursor(Direction dir)
{
	static int lastObj = 0;
	
	if(!menuObjects.empty())
	{
		static sf::Color orgColor = menuObjects.at(0)->getColor();
		lastObj = currentObj;
				
		if(dir == FORWARD)
		{
			if(currentObj != menuObjects.size()-1)
			{
				currentObj++;
			}
			else
			{
				currentObj = 0;
			}
		}
		else if(dir == BACKWARD)
		{
			if(currentObj == 0)
			{
				currentObj = menuObjects.size()-1;
			}
			else
			{
				currentObj--;
			}
		}
		cursor.setSizeFromObject(menuObjects.at(currentObj)->getSizeRect());
		cursor.setPosition(menuObjects.at(currentObj)->getPosition());
		
		if(ColorHighlight)
		{
			menuObjects.at(lastObj)->setColor(orgColor);
			orgColor = menuObjects.at(currentObj)->getColor();
			menuObjects.at(currentObj)->setColor(highlightColor);
		}
	}
}

void Menu::setColorHighlight(bool state, sf::Color color)
{
	ColorHighlight = state;
	highlightColor = color;
	moveCursor(NODIR);
}

void Menu::activate()
{
	if(currentObj != -1)
	{
		action = menuObjects.at(currentObj)->activate();
	}
}

ActionType Menu::getAction()
{
	return action;
}

void Menu::render()
{
	GameEngine::gEngine.FrameTexture.draw(bgSprite);
	GameEngine::gEngine.FrameTexture.draw(buttonRowSprite);

	for(int i=0; i<menuObjects.size(); i++)
	{
		menuObjects.at(i)->draw();
	}
	
	if(!menuObjects.empty())
	{
		cursor.draw();
	}
}


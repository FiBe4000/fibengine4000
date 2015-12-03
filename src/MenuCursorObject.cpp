#include "MenuCursorObject.h"
#include "GameEngine.h"

MenuCursorObject::MenuCursorObject(std::string imPath)
{
	if(!bgTex.loadFromFile(imPath))
	{
		//Engine::stop();
	}
	imSprite.setTexture(bgTex);
}

MenuCursorObject::~MenuCursorObject()
{
}

void MenuCursorObject::setSizeFromObject(sf::FloatRect objSize)
{
	imSprite.setScale((objSize.width+offset)/imSprite.getLocalBounds().width, (objSize.height+offset)/imSprite.getLocalBounds().height);
}

void MenuCursorObject::setPosition(sf::Vector2f pos)
{
	imSprite.setPosition(pos.x - offset/2, pos.y - offset/2);
}

void MenuCursorObject::setColor(sf::Color color)
{
	imSprite.setColor(color);
}

void MenuCursorObject::draw()
{
	GameEngine::gEngine.FrameTexture.draw(imSprite);
}


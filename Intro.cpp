#include "Intro.h"
#include "GameEngine.h"

Intro::Intro() : isDone(false)
{
	if(!texture.loadFromFile("gfx/hattkanin.png"))
	{
		std::cerr << "Intro fail.";
	}
	sprite.setTexture(texture);
	sprite.setPosition(100, 100);
	
	if(!introFont.loadFromFile("data/ETHNOCEN.TTF"))
	{
		std::cerr << "Failed loading font" << std::endl;
		GameEngine::Stop();
	}
	
	introTxtString = "Test Test!";
	introTxt.setFont(introFont);
	introTxt.setString(introTxtString);
	introTxt.setPosition((GameEngine::WINDOW_WIDTH/2) - (introTxt.getCharacterSize() * introTxtString.length() / 2) + 40, GameEngine::WINDOW_HEIGHT/2 - 40);
	introTxt.setScale(1,1);
	
	col = 0;
	colDir = 3;
	progress = 0;
	
	clk.restart();
		
	std::cerr << "Intro created" << std::endl;
}

Intro::~Intro()
{
}

void Intro::Update()
{
	std::cerr << "Intro: update" << std::endl;
	introTxt.setColor(sf::Color(255, 255, 255, col));
	
	if(clk.getElapsedTime() >= sf::milliseconds(10))
	{
		col += colDir;
	
		if(col >= 255 || col <= 0)
		{
			colDir *= -1;
			progress++;
		}
		if(progress == 2)
		{
			isDone = true;
		}
		
		clk.restart();
	}
}

void Intro::Render()
{
	std::cerr << "Intro: render" << std::endl;
	GameEngine::gEngine.App.draw(introTxt);
	//GameEngine::gEngine.App.draw(sprite);
}

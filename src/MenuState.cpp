#include "MenuState.h"
#include "GameEngine.h"

MenuState::MenuState() : StartMenu("/home/fibe/Pictures/Wallpapers/ds2.jpg")
{
	sf::Color color(255,255,255,255);
	static ActionTextObject ato(START_GAME, "", "Start", "data/ETHNOCEN.TTF", 100, GameEngine::gEngine.App.getSize().y/2, color, 35);
	//static ActionTextObject ato2(action, "data/scripts/test.sh", "Steam", "data/ETHNOCEN.TTF", 300, GameEngine::WINDOW_HEIGHT/2, color, 35);
	//static ActionTextObject ato3(action, "data/scripts/test.sh", "Games", "data/ETHNOCEN.TTF", 500, GameEngine::WINDOW_HEIGHT/2, color, 35);
	static ActionTextObject ato4(EXIT, "", "Exit", "data/ETHNOCEN.TTF", 500, GameEngine::gEngine.App.getSize().y/2, color, 35);
	
	ato.setBgImage("gfx/buttonBg.png");
	//ato2.setBgImage("gfx/buttonBg.png");
	//ato3.setBgImage("gfx/buttonBg.png");
	ato4.setBgImage("gfx/buttonBg.png");
	
	ato.background(false);
	//ato2.background(false);
	//ato3.background(false);
	ato4.background(false);
		
	StartMenu.addButtonRowBg("gfx/buttonRow.png", sf::Vector2f(0.f, 300.f));
	StartMenu.addObject(&ato);
	//StartMenu.addObject(&ato2);
	//StartMenu.addObject(&ato3);
	StartMenu.addObject(&ato4);
	
	StartMenu.setColorHighlight(true, sf::Color(0,128,255,255));

	GameEngine::gEngine.App.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
}

MenuState::~MenuState()
{
}

void MenuState::Process()
{
	State::Process();

	GameEngine::gEngine.App.pollEvent(event);
	
	static bool OldRightKeyDown = false;
    static bool OldLeftKeyDown = false;
    static bool OldReturnKeyDown = false;
	
    bool RightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool LeftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool ReturnKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
    
    if(RightKeyDown && !OldRightKeyDown)
    {
        StartMenu.moveCursor(FORWARD);
    }
    if(LeftKeyDown && !OldLeftKeyDown)
    {
        StartMenu.moveCursor(BACKWARD);
    }
    if(ReturnKeyDown && !OldReturnKeyDown)
    {
        StartMenu.activate();
    }
    
	OldRightKeyDown = RightKeyDown;
    OldLeftKeyDown = LeftKeyDown;
    OldReturnKeyDown = ReturnKeyDown;
}

void MenuState::Update()
{
	State::Update();
	
	if(StartMenu.getAction() == START_GAME)
	{
		State::ReqStateChange(GAME_STATE);
	}
	else if(StartMenu.getAction() == EXIT)
	{
		GameEngine::Stop();
	}
}

void MenuState::Render()
{
	GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
	State::Render();
	
	StartMenu.render();
	GameEngine::gEngine.FrameTexture.display();
	
	FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
	GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
	GameEngine::gEngine.App.display();
}

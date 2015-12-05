#include "MenuState.h"
#include "GameEngine.h"

MenuState::MenuState() : StartMenu("gfx/menubg.png")
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

    FadeIn = true;
    FadeOut = false;
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
	    FadeOut = true;
		State::ReqStateChange(GAME_STATE);
	}
	else if(StartMenu.getAction() == EXIT)
	{
	    FadeOut = true;
		GameEngine::Stop();
	}
}

void MenuState::Render()
{
    int opa = 0;
    sf::RectangleShape fadebox(sf::Vector2f(GameEngine::gEngine.FrameTexture.getSize().x*2, GameEngine::gEngine.FrameTexture.getSize().y*2));
    fadebox.setFillColor(sf::Color(0,0,0,255));
    GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());

    if(FadeOut)
    {
        while (opa <= 255)
        {
            fadebox.setFillColor(sf::Color(0,0,0, opa));
            GameEngine::gEngine.FrameTexture.draw(fadebox);
            GameEngine::gEngine.FrameTexture.display();

            //GameEngine::gEngine.PostFxShader.setParameter("timer", GameEngine::gEngine.shaderClock.getElapsedTime().asSeconds()*100);
            FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
            GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
            GameEngine::gEngine.App.display();
            opa += 600 * GameEngine::gEngine.GetFrameTime();
        }
    }
    else if(FadeIn)
    {
        opa = 255;
        while (opa >= 0)
        {
            State::Render();
            StartMenu.render();

            fadebox.setFillColor(sf::Color(0,0,0, opa));
            // Draw fadebox
            GameEngine::gEngine.FrameTexture.draw(fadebox);
            GameEngine::gEngine.FrameTexture.display();

            //GameEngine::gEngine.PostFxShader.setParameter("timer", GameEngine::gEngine.shaderClock.getElapsedTime().asSeconds()*100);
            FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
            GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
            GameEngine::gEngine.App.display();

            opa -= 600 * GameEngine::gEngine.GetFrameTime();
        }
        FadeIn = false;
    }
    else
    {
        State::Render();

        StartMenu.render();
        GameEngine::gEngine.FrameTexture.display();

        FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
        GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
        GameEngine::gEngine.App.display();
    }
}

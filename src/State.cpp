#include "State.h"
#include "GameEngine.h"

State::State() : GStateReq(false), IStateReq(false), MStateReq(false)
{
}

State::~State()
{
}

void State::Process()
{	
    GameEngine::gEngine.App.pollEvent(event);
	
	static bool OldEscKeyDown = false;
    static bool OldF1KeyDown = false;
    static bool OldF2KeyDown = false;
    static bool OldF3KeyDown = false;
	
    bool EscKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    bool F1KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::F1);
    bool F2KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::F2);
    bool F3KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::F3);
    
    if(event.type == sf::Event::Closed)
    {
        GameEngine::Stop();
    }
    if(EscKeyDown && !OldEscKeyDown)
    {
        GameEngine::Stop();
    }
    if((F1KeyDown && !OldF1KeyDown) || GStateReq)
    {
        State* NewState = new GameState();
        GameEngine::gEngine.ChangeState(NewState);
    	GStateReq = false;
    }
    if(F2KeyDown && !OldF2KeyDown || MStateReq)
    {
        State* NewState=new MenuState();
        GameEngine::gEngine.ChangeState(NewState);
        GStateReq = false;
    }
    if((F3KeyDown && !OldF3KeyDown) || IStateReq)
    {
		State* NewState = new IntroState();
		GameEngine::gEngine.ChangeState(NewState);
    	IStateReq = false;
    }

	OldEscKeyDown = EscKeyDown;
    OldF1KeyDown = F1KeyDown;
    OldF2KeyDown = F2KeyDown;
	OldF3KeyDown = F3KeyDown;
}

void State::Update()
{
}

void State::Render()
{
    GameEngine::gEngine.App.clear();
    GameEngine::gEngine.FrameTexture.clear(sf::Color::Black);
}

void State::ReqStateChange(int state)
{
	switch(state)
	{
		case GAME_STATE:
			GStateReq = true;
		break;
		
		case INTRO_STATE:
			IStateReq = true;
		break;
		
		case MENU_STATE:
			MStateReq = true;
		break;	
	}
}


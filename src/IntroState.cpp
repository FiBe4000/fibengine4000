#include "IntroState.h"
#include "GameEngine.h"

IntroState::IntroState()
{
    std::cerr << "Entering IntroState" << std::endl;
   	GameEngine::gEngine.App.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
}

IntroState::~IntroState()
{
}

void IntroState::Process()
{
    State::Process();
}

void IntroState::Update()
{	
	if(intro.IsDone())
	{
		State::ReqStateChange(MENU_STATE);
	}
	else
	{
		intro.Update();
	}
}

void IntroState::Render()
{	
	GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
    State::Render();
    intro.Render();
	GameEngine::gEngine.FrameTexture.display();
	
	FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
	GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
	GameEngine::gEngine.App.display();
}


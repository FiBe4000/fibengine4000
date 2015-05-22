#include "IntroState.h"
#include "GameEngine.h"

IntroState::IntroState()
{
    std::cerr << "Entering IntroState" << std::endl;
}

IntroState::~IntroState()
{
}

void IntroState::Process()
{
	std::cerr << "IntroState: process" << std::endl;
    State::Process();
}

void IntroState::Update()
{
	std::cerr << "IntroState: update" << std::endl;
	
	if(intro.IsDone())
	{
		State::ReqStateChange(GAME_STATE);
	}
	else
	{
		intro.Update();
	}
}

void IntroState::Render()
{
	std::cerr << "IntroState: render" << std::endl;
	
	GameEngine::gEngine.App.setView(GameEngine::gEngine.App.getDefaultView());
    State::Render();
    intro.Render();
    GameEngine::gEngine.App.display();
}


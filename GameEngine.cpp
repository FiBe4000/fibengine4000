#include "GameEngine.h"
#include <iostream>
#include <vector>

GameEngine GameEngine::gEngine;

//Test

GameEngine::GameEngine() : Running(false)
{
    App.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "gEngine");//, sf::Style::Fullscreen);
    App.setFramerateLimit(60);
    App.setVerticalSyncEnabled(true);
    //App.ShowMouseCursor(false);
    //App.SetSize(WINDOW_WIDTH*2, WINDOW_HEIGHT*2);
    state = new GameState();
    changeState = false;
    std::cerr << "Window set up" << std::endl;
}

GameEngine::~GameEngine()
{
    delete state;
}

void GameEngine::Start()
{
    gEngine.Run();
}

void GameEngine::Run()
{
    Running=true;
    std::cerr << "Running main loop" << std::endl;
    while(Running)
    {
    	frameClock.restart();

        if(changeState)
        {
        	std::cerr << "Deleting " << state->p() << std::endl;
            delete state;
            state=NewState;
            changeState=false;
        }

        state->Process();
        state->Update();
        state->Render();
    }
}

void GameEngine::Stop()
{
    gEngine.Running=false;
}

void GameEngine::ChangeState(State* newState)
{
    changeState=true;
    NewState=newState;
}

float GameEngine::GetFrameTime()
{
	return frameClock.getElapsedTime().asSeconds();
}


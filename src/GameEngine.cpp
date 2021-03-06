#include "GameEngine.h"
#include <iostream>
#include <vector>

GameEngine GameEngine::gEngine;

GameEngine::GameEngine() : Running(false)
{
    App.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "gEngine", sf::Style::Fullscreen);
    App.setFramerateLimit(60);
    App.setVerticalSyncEnabled(true);
    App.setMouseCursorVisible(false);

    if(!FrameTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT))
    {
    	Stop();
    }

    state = new IntroState();
    changeState = false;
    std::cerr << "Window set up" << std::endl;

    shaderClock.restart();
    if(!sf::Shader::isAvailable())
	{
    	std::cout << "Shaders not supported" << std::endl;
	}
    if(!PostFxShader.loadFromFile("data/shaders/shader.vert", "data/shaders/shader.frag"))
    {
    	Stop();
    }
    PostFxShader.setParameter("tex", sf::Shader::CurrentTexture);
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
    gEngine.Running=true;
    std::cerr << "Running main loop" << std::endl;
    while(gEngine.Running)
    {
    	frameTime = frameClock.restart().asSeconds();

        if(changeState)
        {
            delete state;
            changeState=false;

            switch(NewState)
            {
                case GAME_STATE:
                    state = new GameState;
                    break;

                case MENU_STATE:
                    state = new MenuState;
                    break;

                case INTRO_STATE:
                    state = new IntroState;
                    break;
            }
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

void GameEngine::ChangeState(int newState)
{
    changeState=true;
    NewState = newState;
}

float GameEngine::GetFrameTime()
{
	return frameTime;
}


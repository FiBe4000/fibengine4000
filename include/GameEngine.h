#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED

/*!
 \file GameEngine.h
 \brief The definition of the GameEngine class.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "GameState.h"
#include "IntroState.h"
#include <iostream>

#define GAME_STATE 0
#define INTRO_STATE 1
#define MENU_STATE 2


/*!
 \class GameEngine
 \brief The GameEngine class contains the main loop of the game along with some very important variables.
 \details The GameEngine class contains a pointer to a State to handle the current state of the game. It also contains the window and a static object of itself.
*/

class GameEngine
{
private:
    /*!
     \brief The pointer to the current State.
    */
    State* state;

    /*!
     \brief A pointer to a new state.
    */
    State* NewState;

    /*!
     \brief Is the game running?
    */
    bool Running;

    /*!
     \brief A bool to check whether the State should be changed or not.
    */
    bool changeState;
    
    sf::Clock frameClock;
	
    /*!
     \brief This method is the main method used for running the game. It contains the main loop.
    */
    void Run();

public:
    /*!
     \brief This variable contains the width of the window.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int WINDOW_WIDTH=600;

    /*!
     \brief This variable contains the height of the window.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int WINDOW_HEIGHT=400;

    /*!
     \brief This variable contains the height of the tiles.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int TILE_HEIGHT=32;

    /*!
     \brief This variable contains the width of the tiles.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int TILE_WIDTH=32;

    /*!
     \brief This variable contains the width of the player.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int PLAYER_WIDTH=13;//28;

    /*!
     \brief This variable contains the height of the player.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const int PLAYER_HEIGHT=18;//30;

    /*!
     \brief This variable contains the value gravitational acceleration in the game.
     \note While every class should be able to reach the variable, but not change it, it's public and const.
    */
    static const double G = 10;

    /*!
     \brief The constructor.
    */
    GameEngine();

    /*!
     \brief The destructor.
    */
    ~GameEngine();

    /*!
     \brief The public method to start the game.
    */
    static void Start();

    /*!
     \brief The method used to stop the game.
    */
    static void Stop();

    /*!
     \brief This method is used to change the current State while running the game.
     \param newState: This pointer to State contains the address to the new State.
    */
    void ChangeState(State* newState);
	
	float GetFrameTime();
	
    /*!
     \brief Get the current State.
     \return The current State.
    */
    State& GetState() { return *state; }
	
	///////////////////////////////////////////////////////////////////////////////////////////////////int GetFrameTime() { return frameTime.getElapsedTime().asSeconds(); }
	
    /*!
     \brief The window in which everything is drawn.
     \note While every class should be able to reach the window, through the static object gEngine, it is public.
    */
    sf::RenderWindow App;
	
    /*!
     \brief This static object of the class itself is used to handle the game and to access the window.
     \note While every class should be able to reach this object, it is public.
    */
    static GameEngine gEngine;
};

#endif // GAMEENGINE_H_INCLUDED

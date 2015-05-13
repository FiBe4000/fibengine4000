#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

/*!
 \file GameState.h
 \brief The definition of the GameState class.
*/

#include "Game.h"
#include "State.h"
#include <string>
//#include <SFML/Graphics.hpp>

/*!
 \class GameState
 \brief The GameState class handles the top-down part of the game.
 \details GameState inherits from State. It handles the processing of inputs, the updating of the game world and the rendering of the game world in top-down mode. It also configures the window and the view, the camera, to the top-down mode.
*/

class GameState : public State
{
private:
    /*!
     \brief The object which contains the player and the level.
    */
    Game game;

    /*!
     \brief The camera which handles the scrolling of the map.
    */
    sf::View GameView;
    
    sf::Clock frameClock;

    /*!
     \brief An array of bools representing if a border is in the line-of-sight of the player.
    */
    bool NearBorder[4];

    /*!
     \brief A bool used for checking whether a new level should be loaded or not.
    */
    bool IsNewLevel;
	
	/*!
	 \brief A bool used for checking whether the player is dead or not.
	*/
	bool IsPlayerDead;
	bool Paused;
public:
    /*!
     \brief The constructor.
    */
    GameState();

    /*!
     \brief The virtual destructor.
    */
    virtual ~GameState();

    /*!
     \brief The method processing inputs. It's checking if any of the arrow keys or the left shift key are down.
    */
    void Process();

    /*!
     \brief This is the render method. It renders the game world and the player.
    */
    void Render();

    /*!
     \brief The update method is used for updating the game world.
    */
    void Update();

    /*!
     \brief Get the game object.
     \return The game object.
    */
    //Game& GetGame() { return game; }
    
    std::string p() { return "GameState"; } 
};

#endif // GAMESTATE_H_INCLUDED

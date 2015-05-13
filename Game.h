#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

/*!
 \file Game.h
 \brief The definition of the Game class.
*/

//#include "Player.h"
#include "Tilegrid.h"

/*!
 \class Game
 \brief The Game class consists of one object of the class Player and one object of the class Tilegrid.
 \note The Game class is almost the same as the Level class but the Game class handles the top-down view of the game while the Level class handles the side-scrolling part of the game.
*/

class Game
{
private:
    

    /*!
     \brief The tilegrid of the game.
    */
    Tilegrid tilegrid;

public:
    /*!
     \brief The constructor.
    */
    Game();

    /*!
     \brief The virtual destructor.
    */
    virtual ~Game();

    /*!
     \brief Get the player.
     \return The player.
    */
    Player& GetPlayer() { return tilegrid.GetPlayer(); }

    /*!
     \brief Get the tilegrid.
     \return The tilegrid.
    */
    Tilegrid& GetTilegrid() { return tilegrid; }
};

#endif // GAME_H_INCLUDED

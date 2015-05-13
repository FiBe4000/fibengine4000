#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

/*!
 \file Player.h
 \brief The definition of the Player class.
*/

#include "Character.h"
//#include "Stats.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <sstream>

/*!
 \class Player
 \brief The Player class describes the player.
 \details The Player class inherits from the Character class which means that an object of Player is an animated character. There are several methods for moving the player up and down and to perform a jump.
*/

class Player : public Character
{
private:
    /*!
     \brief The players current direction.
    */
    int direction;

    /*!
     \brief The players current speed in the x-axis.
    */
    float xSpeed;

    /*!
     \brief The players current speed in the y-axis.
    */
    float ySpeed;

    /*!
     \brief The initial speed of the player.
    */
    float v0;

    /*!
     \brief A bool used for checking whether the player is jumping or not.
    */
    bool IsJumping;

    /*!
     \brief A bool used for checking whether the player is falling or not.
    */
    bool IsFalling;

    /*!
     \brief The players stats.
    */
    //Stats PlayerStats;

    /*!
     \brief The timer used in the physical calculations.
    */
    //sf::Clock gravClock;

    /*!
     \brief The font used for the StatsString.
    */
    sf::Font StatsFont;

    /*!
     \brief The string used for writing the stats.
    */
    sf::String StatsString;
    
    std::string id;
    
public:
    /*!
     \brief The constructor.
    */
    Player();

    /*!
     \brief The destructor.
    */
    virtual ~Player();

    /*!
     \brief Get the player x-axis position.
    */
    const float GetX() const { return position.x; }

    /*!
     \brief Get the player y-axis position.
    */
    const float GetY() const { return position.y; }

    /*!
     \brief Get the player x-axis speed.
     \return The x-axis speed.
    */
    const float GetPlayerXSpeed() const { return xSpeed; }

    /*!
     \brief Get the player y-axis speed.
     \return The y-axis speed.
    */
    const float GetPlayerYSpeed() const { return ySpeed; }
	
	const std::string GetId() { return id; }
	
    /*!
     \brief Set the player x-axis position to the parameter.
     \param newX : The new x-axis position.
    */
    void SetX(float newX);

    /*!
     \brief Set the player y-axis position to the parameter.
     \param newY : The new y-axis position.
    */
    void SetY(float newY);

    /*!
     \brief Set the player in run mode.
    */
    //void Run() { xSpeed = PlayerStats.GetRunSpeed(); }

    /*!
     \brief Reset the player into walk mode.
    */
    void ResetRun() { xSpeed = 1; }

    /*!
     \brief Toggle the jump mode on.
    */
    void Jump();

    /*!
     \brief Update the player jump.
     \param CanMove : A bool representing whether the player can move or not.
    */
    void UpdateJump(bool CanMove);

    /*!
     \brief Reset the jump variables.
    */
    void ResetJump();

    /*!
     \brief Kill the player, decrease the number of lives by one.
    */
    void Death() { /*PlayerStats.DecreaseLives()*/; }

    /*!
     \brief Move the player down.
     \param CanMove : A bool representing whether the player can move or not.
    */
    void movePlayerDown(bool CanMove);

    /*!
     \brief Move the player up.
     \param CanMove : A bool representing whether the player can move or not.
    */
    void movePlayerUp(bool CanMove);

    /*!
     \brief Move the player right.
     \param CanMove : A bool representing whether the player can move or not.
    */
    void movePlayerRight(bool CanMove);

    /*!
     \brief Move the player left.
     \param CanMove : A bool representing whether the player can move or not.
    */
    void movePlayerLeft(bool CanMove);

    /*!
     \brief Check whether the player is jumping or not.
     \return A bool representing whether the player is jumping or not.
    */
    bool isJumping() { return IsJumping; }

    /*!
     \brief Check whether the player is falling or not.
     \return A bool representing whether the player is falling or not.
    */
    bool isFalling() { return IsFalling; }

    /*!
     \brief Get the player stats.
     \return The player stats.
    */
    //Stats& GetPlayerStats() { return PlayerStats; }

    /*!
     \brief Get the StatsString variable.
     \return The string containing the stats.
    */
    sf::String& GetStatsString();
};

#endif // PLAYER_H_INCLUDED

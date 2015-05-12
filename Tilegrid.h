#ifndef TILEGRID_H_INCLUDED
#define TILEGRID_H_INCLUDED

/*!
 \file Tilegrid.h
 \brief The definition of the Tilegrid class.
*/

#include "Tile.h"
//#include "Player.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Player.h"
#include "Character.h"
#include "NPC.h"
/*!
 \class Tilegrid
 \brief The Tilegrid class represents the tilegrid of a level.
 \details Tilegrid contains a two-dimensional vector which represents the level. This vector contains objects of the Tile class. In the Tilegrid class collision detection is checked. Updating, loading and rendering levels are three other features.
*/

class Tilegrid
{
private:
	/*!
     \brief The player.
    */
    Player player;
    
    /*!
     \brief The image of the tileset.
    */
    sf::Texture TileSet;

    /*!
     \brief The sprite used for drawing.
    */
    sf::Sprite sprite;
	
	/*!
     \brief The clock used for the level time.
    */
    sf::Clock LevelTime;
    
    /*!
     \brief Is the player dead?
    */
    bool isPlayerDead;

    /*!
     \brief Should another level be loaded?
    */
    bool isNewLevel;

    /*!
     \brief The two-dimensional vector representing the level.
    */
    std::vector< std::vector<Tile> > level;
	
	std::vector<NPC*> npcs;
	
    /*!
     \brief A string containing the name of the current level.
    */
    std::string currentLevel;

    /*!
     \brief An integer representing the width of the level.
    */
    int LevelWidth;

    /*!
     \brief An integer representing the height of the level.
    */
    int LevelHeight;

    /*!
     \brief An integer representing the new x-axis position the player will get.
    */
    int PlayerNewX;

    /*!
     \brief An integer representing the new y-axis position the player will get.
    */
    int PlayerNewY;

    /*!
     \brief The time limit of the current level.
    */
    int TimeLimit;

public:
    /*!
     \brief The constructor.
     \param LevelName : Containing the name of the first level to be loaded.
    */
    Tilegrid(std::string LevelName);

    /*!
     \brief The virtual destructor.
    */
    virtual ~Tilegrid();

    /*!
     \brief Get the width of the current level.
     \return The width of the level.
    */
    const int GetLevelWidth() const { return LevelWidth; }

    /*!
     \brief Get the height of the current level.
     \return The height of the current level.
    */
    const int GetLevelHeight() const { return LevelHeight; }

    /*!
     \brief Get the new x-axis position for the player.
     \return The new x-axis position for the player.
    */
    const int GetNewX() const { return PlayerNewX; }

    /*!
     \brief Get the new y-axis position for the player.
     \return The new y-axis position for the player.
    */
    const int GetNewY() const { return PlayerNewY; }

    /*!
     \brief The method used for the rendering of all tiles.
     \param player : The object player. Used for getting the player position.
     \param NearBorder : Used for checking if the player is in line-of-sight of a border.
    */
    void Render(Player& player, bool NearBorder[]);

    /*!
     \brief A method used for loading a level.
     \param FileName : Contains the FileName of the level to be loaded.
    */
    void LoadTilegrid(std::string FileName);

    /*!
     \brief This method checks whether a special event should be processed or not.
     \param x : The x-axis position of where the method will check.
     \param y : The y-axis position of where the method will check.
    */
    void UpdateTilegrid(float x, float y);
	void UpdateNPCs();
	void SpawnNPCs();
	void DeleteNPCs();
	
    /*!
     \brief Is the player dead?
     \return A bool with the value true if the player is dead or the value false if the player is alive.
    */
    const bool IsPlayerDead() const { return isPlayerDead; }

    /*!
     \brief Is a new level loaded?
     \return A bool with the value true if a new level is loaded or the value false if the current level is still running.
    */
    const bool IsNewLevel() const { return isNewLevel; }

    /*!
     \brief Is the position determined by the parameters accessible?
     \param x : The x-axis position of which the method will do a collision detection check.
     \param y : The y-axis position of which the method will do a collision detection check.
    */
    bool IsAccessible(int x, int y, int width, int height, std::string id) const;

    /*!
     \brief Get the two-dimensional level vector.
     \return The two-dimensional level vector.
    */
    const std::vector< std::vector<Tile> >& getLevel ()  const { return level; };
	
	Player& GetPlayer() { return player; }
	
    /*!
     \brief Get the string containing the current time left on the level.
     \return The string containing the current time left on the level.
    */
    sf::String& GetTimeString();
};

#endif // TILEGRID_H_INCLUDED

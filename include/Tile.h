#ifndef TILET_H_INCLUDED
#define TILET_H_INCLUDED

/*!
 \file TileT.h
 \brief The definition of the Tile class.
*/

#include <SFML/Graphics.hpp>
#include <string>

/*!
 \class Tile
 \brief Each object of the Tile class represents one tile.
 \details An object of the Tile class contains variables determining which image should be applied to the tile, if it's accessible etc.
*/

class Tile
{
private:
    /*!
     \brief A bool determining whether the tile is accessible or not.
    */
    bool IsAccessible;

    /*!
     \brief An int determining which image will be applied to the tile.
    */
    int imNumber;

    /*!
     \brief A string containing a special event or a filename. If it's empty in one tile there is no special event on that tile.
    */
    std::string fileName;

    /*!
     \brief A rectangle framing the area of the tileset determined by the integer imNumber.
    */
    sf::Rect<int> rect;

public:
    /*!
     \brief The standard constructor.
    */
    Tile();

    /*!
     \brief A second constructor.
     \param num : Set the tile's imNumber to parameter.
     \param isAccessible : Set the tile's IsAccessible to parameter.
     \param fName : Set the tile's string filename to parameter.
    */
    Tile(int num, bool isAccessible, std::string fName, sf::Vector2u tileSetSize);

    /*!
     \brief The destructor.
    */
    virtual ~Tile();

    /*!
     \brief Get the filename string.
     \return The filename.
    */
    std::string GetFileName() { return fileName; }

    /*!
     \brief Is the tile accessible?
     \return A bool representing if the tile is accessible or not.
    */
    const bool isAccessible() const { return IsAccessible; }

    /*!
     \brief Get the rect determining which picture should be applied to the tile.
    */
    sf::Rect<int>& GetRect() { return rect; }

    /*!
     \brief Set the rect to the parameter.
     \param newRect : Set the rect to parameter.
    */
    void SetRect(sf::Rect<int> newRect) { rect = newRect; }
};

#endif // TILET_H_INCLUDED

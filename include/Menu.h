#ifndef MENU_H_
#define MENU_H_

/*!
 \file Menu.h
 \brief The definition of the Menu class.
*/

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
//#include "MenuObject.h"

/*!
 \class Menu
 \brief A class for easily creating a game menu.
 \note The class is currently incomplete.
*/

class Menu
{
private:
    /*!
     \brief The vector containing the MenuObject objects.
    */
	//std::vector<MenuObject> MenuObjects;

	/*!
	 \brief The sprite used for rendering.
	*/
	sf::Sprite renderingSprite;

	/*!
	 \brief The font used to the text.
	*/
	sf::Font font;
	
public:
    /*!
     \brief The constructor.
    */
	Menu();

	/*!
	 \brief The virtual destructor.
	*/
	virtual ~Menu();

    /*!
     \brief A method used for adding an image to the menu.
     \param imName : The filename of the image.
     \param x : The x-axis position of the image.
     \param y : The y-axis position of the image.
    */
	void AddImage(std::string imName, int x, int y);

	/*!
	 \brief A method used for adding a text to the menu.
	 \param txt : The text to be shown in the menu.
	 \param txtSize : The size of the text.
	 \param x : The x-axis position of the text.
	 \param y : The y-axis position of the text.
	*/
	void AddText(std::string txt, int txtSize, int x, int y);

	/*!
	 \brief Set the color of the text.
	 \param c1 : The red part of the color.
	 \param c2 : The green part of the color.
	 \param c3 : The Blue part of the color.
	*/
	void SetTextColor(int c1, int c2, int c3);

	/*!
	 \brief The rendering method.
	*/
	void Render();
};

#endif /* MENU_H_ */

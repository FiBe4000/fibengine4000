#ifndef INTRO_H_INCLUDED
#define INTRO_H_INCLUDED

/*!
 \file Intro.h
 \brief The definition of the Intro class.
*/

#include <SFML/Graphics.hpp>

/*!
 \class Intro
 \brief A class used for the intro to the game.
 \note The class is currently incomplete.
*/

class Intro
{
private:
    /*!
     \brief The sprite used for rendering.
    */
	sf::Sprite sprite;

	/*!
	 \brief The image containing the logotype.
	*/
	sf::Texture texture;
	
	sf::Text introTxt;
	
	sf::Clock clk;
	
	sf::Font introFont;
	
	std::string introTxtString;
	/*!
	 \brief A temporary variable used for handling color.
	*/
	int col;
	
	/*!
	 \brief A temporary variable used for handling color.
	*/
	int colDir;
	int progress;
	
	bool isDone;

public:
    /*!
     \brief The constructor
    */
	Intro();

	/*!
	 \brief The destructor.
	*/
	virtual ~Intro();

    /*!
     \brief The update method.
    */
	void Update();

	/*!
	 \brief The rendering method.
	*/
	void Render();
	
	bool IsDone() { return isDone; }
};

#endif /* INTRO_H_ */

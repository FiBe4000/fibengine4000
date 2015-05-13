#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

/*!
 \file Character.h
 \brief Definition of the Character class.
*/

#include "AnimatedSprite.h"
#include <SFML/System.hpp>
#include <iostream>
#include <string>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

/*!
 \class Character
 \brief This class describes an animated game character.
 \details The Character class has one object of sf::Image, one object of Animated and an array of Anim. The sf::Image handles the image of the character. The Animated handles the animation of the character along with the array of Anim which consists of all the frames needed to animate the character.
*/

class Character
{
private:
    /*!
     \brief The character image.
    */
    sf::Texture characterTexture;

    /*!
     \brief The animation of the character.
    */
    AnimatedSprite animChar;

	Animation* currentAnimation;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;
	
	sf::Time FrameTime;
	
	sf::Clock FrameClock;
	
	bool Moving;

protected:
	sf::Vector2f position;
	sf::Vector2f movement;
	
public:
    /*!
     \brief The constructor.
    */
    Character(std::string charFilename);

    /*!
     \brief The virtual destructor.
    */
    virtual ~Character();

    /*!
     \brief Get the characters Animated.
     \return The animation of the character.
    */
    AnimatedSprite& GetAnimation() { return animChar; }

	/*!
     \brief Move the character down.
     \param CanMove : A bool representing whether the character can move or not.
    */
    void moveDown(bool CanMove, float moveSpeed);

    /*!
     \brief Move the character up.
     \param CanMove : A bool representing whether the character can move or not.
    */
    void moveUp(bool CanMove, float moveSpeed);

    /*!
     \brief Move the character right.
     \param CanMove : A bool representing whether the character can move or not.
    */
    void moveRight(bool CanMove, float moveSpeed);

    /*!
     \brief Move the character left.
     \param CanMove : A bool representing whether the character can move or not.
    */
    void moveLeft(bool CanMove, float moveSpeed);
    
    void stop();
    
    void update();
    
    void updatePosition() { animChar.setPosition(position); }
};

#endif // CHARACTER_H_INCLUDED

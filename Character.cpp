#include "Character.h"
#include "GameEngine.h"

Character::Character(std::string charFilename) : animChar(sf::seconds(0.2), true, false)
{	
	char filename[30];
	
	int i;
	for(i=0; i<charFilename.length(); i++)
   		filename[i] = charFilename.at(i);
	filename[i] = '\0';
	
    if(!characterTexture.loadFromFile(filename))
    {
    	std::cerr << "Error: " << charFilename << " could not be found" << std::endl;
        GameEngine::Stop();
    }
    characterTexture.setSmooth(false);
	
	walkingAnimationDown.setSpriteSheet(characterTexture);
	walkingAnimationLeft.setSpriteSheet(characterTexture);
	walkingAnimationRight.setSpriteSheet(characterTexture);
	walkingAnimationUp.setSpriteSheet(characterTexture);
	
    walkingAnimationUp.addFrame(sf::IntRect(24,0,13,18));
    walkingAnimationUp.addFrame(sf::IntRect(48,1,13,18));
    walkingAnimationUp.addFrame(sf::IntRect(24,0,13,18));
    walkingAnimationUp.addFrame(sf::IntRect(0,1,13,18));

    walkingAnimationDown.addFrame(sf::IntRect(24,64,13,18));
    walkingAnimationDown.addFrame(sf::IntRect(48,65,13,18));
    walkingAnimationDown.addFrame(sf::IntRect(24,64,13,18));
    walkingAnimationDown.addFrame(sf::IntRect(0,65,13,18));

    walkingAnimationRight.addFrame(sf::IntRect(24,32,13,18));
    walkingAnimationRight.addFrame(sf::IntRect(48,33,13,18));
    walkingAnimationRight.addFrame(sf::IntRect(24,32,13,18));
    walkingAnimationRight.addFrame(sf::IntRect(0,33,13,18));

    walkingAnimationLeft.addFrame(sf::IntRect(24,96,13,18));
    walkingAnimationLeft.addFrame(sf::IntRect(48,97,13,18));
    walkingAnimationLeft.addFrame(sf::IntRect(24,96,13,18));
    walkingAnimationLeft.addFrame(sf::IntRect(0,97,13,18));

/*
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));	
*/	
	position.x = 0.f;
	position.y = 0.f;
	
	animChar.setPosition(position);
	Animation* currentAnimation = &walkingAnimationRight;
	animChar.play(*currentAnimation);
	Moving = false;
}

Character::~Character()
{
}

void Character::moveDown(bool CanMove, float moveSpeed)
{
	FrameTime = FrameClock.restart();
	
	currentAnimation = &walkingAnimationDown;
	animChar.play(*currentAnimation);
	//movement = sf::Vector2f(0.f, 0.f);
	//animChar.play(*currentAnimation);
	
    if(CanMove)
    {
        position.y += moveSpeed;
        //movement.y += moveSpeed;
        Moving = true;
        //GetAnimation().move(position * FrameTime.asSeconds());
    }
    else
    {
    	animChar.stop();
    }
}

void Character::moveUp(bool CanMove, float moveSpeed)
{
	FrameTime = FrameClock.restart();
	
	currentAnimation = &walkingAnimationUp;
	animChar.play(*currentAnimation);
	//movement = sf::Vector2f(0.f, 0.f);
	//animChar.play(*currentAnimation);
	
    if(CanMove)
    {
        position.y -= moveSpeed;
        //movement.y -= moveSpeed;
        Moving = true;
        //GetAnimation().move(position * FrameTime.asSeconds());
    }
    else
    {
    	animChar.stop();
    }
}

void Character::moveRight(bool CanMove, float moveSpeed)
{
   	FrameTime = FrameClock.restart();
	
	currentAnimation = &walkingAnimationRight;
	animChar.play(*currentAnimation);
	//movement = sf::Vector2f(0.f, 0.f);
	//animChar.play(*currentAnimation);
	
    if(CanMove)
    {
        position.x += moveSpeed;
        //movement.x += moveSpeed;
        Moving = true;
        //GetAnimation().move(position * FrameTime.asSeconds());
    }
    else
    {
    	animChar.stop();
    }
}

void Character::moveLeft(bool CanMove, float moveSpeed)
{
	FrameTime = FrameClock.restart();
	
	currentAnimation = &walkingAnimationLeft;
	animChar.play(*currentAnimation);
	//movement = sf::Vector2f(0.f, 0.f);
	//animChar.play(*currentAnimation);
	
    if(CanMove)
    {
        position.x -= moveSpeed;
        //movement.x -= moveSpeed;
        Moving = true;
        //GetAnimation().move(position * FrameTime.asSeconds());
    }
    else
    {
    	animChar.stop();
    }
}

void Character::stop()
{
	Moving = false;
	//movement = sf::Vector2f(0.f, 0.f);
}

void Character::update() 
{
	if(!Moving)
	{
		animChar.stop();
	}
	//GetAnimation().move(movement * FrameTime.asSeconds());
	updatePosition();
	animChar.update(FrameTime);
}



#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include "State.h"
#include "Menu.h"
#include "MenuObject.h"
#include "ActionTextObject.h"

class MenuState : public State
{
private:
    Menu StartMenu;

	sf::Sprite FrameSprite;
    bool FadeIn;
    bool FadeOut;

public:
    MenuState();
	virtual ~MenuState();

	void Process();
	void Update();
	void Render();
};

#endif //MENUSTATE_H_INCLUDED

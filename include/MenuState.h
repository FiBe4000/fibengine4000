#ifndef MENUSTATE_H_
#define MENUSTATE_H_

/*!
 \file MenuState.h
 \brief The definition of the MenuState class.
*/

#include "State.h"
#include "Menu.h"

/*!
 \class MenuState
 \brief The MenuState class handles all game menus.
 \details The MenuState class inherits from the State class.
 \note The class is currently incomplete.
*/

class MenuState : public State
{
private:
    /*!
     \brief The object of the class Menu.
    */
	Menu StartMenu;

public:
    /*!
     \brief The constructor.
    */
	MenuState();

	/*!
	 \brief The virtual destructor.
	*/
	virtual ~MenuState();

    /*!
     \brief The process method takes care of all inputs.
    */
	void Process();

	/*!
	 \brief The update method.
	*/
	void Update();

	/*!
	 \brief The rendering method.
	*/
	void Render();
};

#endif /* MENUSTATE_H_ */

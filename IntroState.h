#ifndef INTROSTATE_H_INCLUDED
#define INTROSTATE_H_INCLUDED

/*!
 \file IntroState.h
 \brief The definition of the IntroState class.
*/

#include "State.h"
#include "Intro.h"
#include <string>
/*!
 \class IntroState
 \brief A state handling the intro to the game.
 \details The class inherits from the State class.
 \note The class is currently incomplete.
*/

class IntroState : public State
{
private:
    /*!
     \brief The intro the class is supposed to handle.
    */
    Intro intro;
	
public:
    /*!
     \brief The constructor.
    */
    IntroState();

    /*!
     \brief The destructor.
    */
    ~IntroState();

    /*!
     \brief The process method handles all inputs.
    */
    void Process();

    /*!
     \brief The rendering method.
    */
    void Render();

    /*!
     \brief The update method.
    */
    void Update();
    
    std::string p() { return "IntroState"; }
};

#endif // INTROSTATE_H_INCLUDED

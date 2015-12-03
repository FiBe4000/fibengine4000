#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

/*!
 \file State.h
 \brief The definition of the State class.
*/

#include <SFML/Graphics.hpp>
#include <string>

/*!
 \class State
 \brief
*/

class State
{
private:
	bool GStateReq;
	bool IStateReq;
	bool MStateReq;
				
public:
    /*!
     \brief The sf::Event used by all states.
     \note While all States are supposed to be able to reach the event it is public.
    */
    sf::Event event;

    /*!
     \brief The constructor.
    */
    State();

    /*!
     \brief The virtual destructor.
    */
    virtual ~State();

    /*!
     \brief The virtual process method used for processing some basic inputs like exiting the program when pushing the escape key or when the window is closed.
    */
    virtual void Process();

    /*!
     \brief The virtual update method not used for anything but the inheritance.
    */
    virtual void Update();

    /*!
     \brief The virtual render method. It contains the Clear() method in the RenderWindow.
    */
    virtual void Render();
    
    void ReqStateChange(int state);
    
    virtual std::string p() { return "State"; }
};

#endif // STATE_H_INCLUDED

#ifndef BEHAVIOR_H_INCLUDED
#define BEHAVIOR_H_INCLUDED

#include <iostream>

class Behavior
{
private:
    
public:
    Behavior();
    virtual ~Behavior();
    
    virtual void Update() { ; };
};

#endif // BEHAVIOR_H_INCLUDED

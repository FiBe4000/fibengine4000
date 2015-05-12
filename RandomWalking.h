#ifndef RANDOMWALKING_H_INCLUDED
#define RANDOMWALKING_H_INCLUDED

#include "Behavior.h"
#include <iostream>

class RandomWalking : public Behavior
{
private:
    
public:
    RandomWalking();
    virtual ~RandomWalking();
    
    void Update();
};

#endif // RANDOMWALKING_H_INCLUDED

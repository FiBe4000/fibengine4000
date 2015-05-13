#ifndef AIMANAGER_H_INCLUDED
#define AIMANAGER_H_INCLUDED

#include "Behavior.h"
#include "RandomWalking.h"
#include <iostream>
#include <fstream>

class AIManager
{
private:
    Behavior* behavior;
public:
    AIManager();
    virtual ~AIManager();
    
    void ReadBehaviorFile();
    void Update();
};

#endif // AIManager_H_INCLUDED

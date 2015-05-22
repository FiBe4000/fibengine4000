#include "AIManager.h"

AIManager::AIManager()
{
	behavior = new RandomWalking();
}

AIManager::~AIManager()
{
	delete behavior;
}

void AIManager::ReadBehaviorFile()
{
	
}

void AIManager::Update()
{
	behavior->Update();
}


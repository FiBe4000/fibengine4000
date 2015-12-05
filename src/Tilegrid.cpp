#include "Tilegrid.h"
#include "GameEngine.h"

Tilegrid::Tilegrid(std::string LevelName)
{
	isNewLevel = true;
    isPlayerDead = false;
    currentLevel = LevelName;
    LoadTilegrid(LevelName);
}

Tilegrid::~Tilegrid()
{
	std::cerr << "Deleting npcs and enemies" << std::endl;
	for(int i=0; i<npcs.size(); i++)
	{
		delete npcs.at(i);
	}
}

void Tilegrid::Render(Player& player, bool NearBorder[])
{
	//std::cerr << "Tilegrid: Render" << std::endl;

	// Calculate the tiles the player is within range, plus extra offsets.
	int extra_offsetXa = 1;
	int extra_offsetXb = 1;
	int extra_offsetYa = 1;
	int extra_offsetYb = 1;

	if(NearBorder[0])
	   extra_offsetYb = 1;
	if(NearBorder[1])
	   extra_offsetYa = 4;
	if(NearBorder[2])
	   extra_offsetXa = 2;
	if(NearBorder[3])
	   extra_offsetXb = 3;

	int Xa = int( -0.5f+((float)player.GetX()-(float)GameEngine::WINDOW_WIDTH/2)/(float)GameEngine::TILE_WIDTH ) -extra_offsetXa;
	int Xb = int( 0.5f+((float)player.GetX()+(float)GameEngine::WINDOW_WIDTH/2)/(float)GameEngine::TILE_WIDTH ) +extra_offsetXb;

	int Ya = int( -0.5f+((float)player.GetY()-(float)GameEngine::WINDOW_HEIGHT/2)/(float)GameEngine::TILE_HEIGHT ) -extra_offsetYa;
	int Yb = int( 0.5f+((float)player.GetY()+(float)GameEngine::WINDOW_HEIGHT/2)/(float)GameEngine::TILE_HEIGHT ) +extra_offsetYb;

	// If the variables are not in range, make them so.
	(Xa < 0) ? Xa=0 : 0;
	(Xb > LevelWidth) ? Xb=LevelWidth : 0;
	(Ya < 0) ? Ya=0 : 0;
	(Yb > LevelHeight) ? Yb=LevelHeight : 0;

	for(int i=Xa; i<Xb; i++)
	{
		for(int j=Ya; j<Yb; j++)
		{
			// Set position
			sprite.setPosition(sf::Vector2f(float(i*GameEngine::TILE_WIDTH), float(j*GameEngine::TILE_HEIGHT)));
			sprite.setTextureRect(level[j][i].GetRect());
			GameEngine::gEngine.FrameTexture.draw(sprite);
		}
	}

	for(int i=0; i<npcs.size(); i++)
	{

		int NXa = int(-0.5f+((float)player.GetX()-(float)GameEngine::WINDOW_WIDTH/2)) - extra_offsetXa * GameEngine::TILE_WIDTH;
		int NXb = int(0.5f+((float)player.GetX()+(float)GameEngine::WINDOW_WIDTH/2)) + extra_offsetXb * GameEngine::TILE_WIDTH;

		int NYa = int(-0.5f+((float)player.GetY()-(float)GameEngine::WINDOW_HEIGHT/2)) - extra_offsetYa * GameEngine::TILE_HEIGHT;
		int NYb = int(0.5f+((float)player.GetY()+(float)GameEngine::WINDOW_HEIGHT/2)) + extra_offsetYb * GameEngine::TILE_HEIGHT;

		if(npcs.at(i)->GetX() >= NXa && npcs.at(i)->GetX() <= NXb && npcs.at(i)->GetY() >= NYa && npcs.at(i)->GetY() <= NYb)
		{
			GameEngine::gEngine.FrameTexture.draw(npcs.at(i)->GetAnimation());
		}
	}
}

bool Tilegrid::IsAccessible(int x, int y, int width, int height, std::string id) const
{
	float pX = player.GetX();
	float pY = player.GetY();
	int pWidth = GameEngine::PLAYER_WIDTH;
	int pHeight = GameEngine::PLAYER_HEIGHT;

    if(x<0 || y<0 || y>GameEngine::TILE_HEIGHT*LevelHeight-height-1 || x>GameEngine::GameEngine::TILE_WIDTH*LevelWidth-width-1)
    {
        return false;
    }

    //std::cerr << "upper left" << " x=" << x << " y=" << y << std::endl;
    if(!level[int((y+15)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].isAccessible()) //�vre v�nstra h�rnet
    {
    	//std::cerr << "Upp" << std::endl;
        return false;
    }

    //std::cerr << "lower right" << std::endl;
    if(!level[int((y+height)/GameEngine::TILE_HEIGHT)][int((x+width)/GameEngine::TILE_WIDTH)].isAccessible()) //Nedre h�gra h�rnet
    {
    	//std::cerr << "Ner" << std::endl;
    	return false;
    }

    //std::cerr << "lower left" << std::endl;
    if(!level[int((y+height)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].isAccessible()) //Nedre v�nstra h�rnet
    {
    	//std::cerr << "Ner" << std::endl;
    	return false;
    }

    //std::cerr << "upper right" << std::endl;
    if(!level[int((y+15)/GameEngine::TILE_HEIGHT)][int((x+width)/GameEngine::TILE_WIDTH)].isAccessible()) //�vre h�gra h�rnet
    {
    	//std::cerr << "Upp" << std::endl;
        return false;
    }

	if(((x+width >= pX && x+width <= pX+pWidth) || (x >= pX && x <= pX+pWidth)) && id != "player")
	{
		if((y >= pY && y <= pY+pHeight) || (y+height >= pY && y+height <= pY+pHeight))
		{
			return false;
		}
	}

	for(int i=0; i<npcs.size(); i++)
	{
		float npcX = npcs.at(i)->GetX();
		float npcY = npcs.at(i)->GetY();
		int npcWidth = npcs.at(i)->GetWidth();
		int npcHeight = npcs.at(i)->GetHeight();

		if(((x+width >= npcX && x+width <= npcX+npcWidth) || (x >= npcX && x <= npcX+npcWidth)) && id != npcs.at(i)->GetId())
		{
			if((y >= npcY && y <= npcY+npcHeight) || (y+height >= npcY && y+height <= npcY+npcHeight))
			{
				return false;
			}
		}
	}

    return true;
}

sf::String& Tilegrid::GetTimeString()
{
}

void Tilegrid::UpdateTilegrid(float x, float y)
{
	std::string tempStr = "";

	if(!level[int((y+15)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].GetFileName().empty())
	{
		tempStr = level[int((y+15)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].GetFileName();
	}

	if(!level[int((y+GameEngine::PLAYER_HEIGHT)/GameEngine::TILE_HEIGHT)][int((x+GameEngine::PLAYER_WIDTH)/GameEngine::TILE_WIDTH)].GetFileName().empty())
	{
		tempStr = level[int((y+GameEngine::PLAYER_HEIGHT)/GameEngine::TILE_HEIGHT)][int((x+GameEngine::PLAYER_WIDTH)/GameEngine::TILE_WIDTH)].GetFileName();
	}

	if(!level[int((y+GameEngine::PLAYER_HEIGHT)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].GetFileName().empty())
	{
		tempStr = level[int((y+GameEngine::PLAYER_HEIGHT)/GameEngine::TILE_HEIGHT)][int(x/GameEngine::TILE_WIDTH)].GetFileName();
	}

	if(!level[int((y+15)/GameEngine::TILE_HEIGHT)][int((x+GameEngine::PLAYER_WIDTH)/GameEngine::TILE_WIDTH)].GetFileName().empty())
	{
		tempStr = level[int((y+15)/GameEngine::TILE_HEIGHT)][int((x+GameEngine::PLAYER_WIDTH)/GameEngine::TILE_WIDTH)].GetFileName();
	}

	if(!tempStr.empty() || (int(LevelTime.getElapsedTime().asSeconds()) >= TimeLimit) && TimeLimit != 0)
	{
		int tt = int(LevelTime.getElapsedTime().asSeconds());

		if(tempStr == "PlayerDeath" || ((int(LevelTime.getElapsedTime().asSeconds()) >= TimeLimit) && TimeLimit != 0))
		{
			std::cerr << "Dead" << std::endl;
			char fileName[80] = "";
			int j;

			for(j=0; j<currentLevel.substr(6, currentLevel.length()).length(); j++)
			{
				fileName[j] = currentLevel.substr(6, currentLevel.length()).at(j);
			}
			fileName[j] = '\0';
			std::cerr << fileName << std::endl;
			for(int i=0; i<LevelHeight; i++)
			{
				level.at(i).clear();
			}

			isNewLevel = true;
			isPlayerDead = true;
			level.clear();
			LoadTilegrid(fileName);
			LevelTime.restart();
		}
		else if(tempStr.substr(0, 5) == "Level")
		{
			char fileName[80] = "";
			int j;

			for(j=0; j<tempStr.substr(6, tempStr.length()).length(); j++)
			{
				fileName[j] = tempStr.substr(6, tempStr.length()).at(j);
			}
			fileName[j] = '\0';

			for(int i=0; i<LevelHeight; i++)
			{
				level.at(i).clear();
			}

			isNewLevel = true;
			level.clear();
			currentLevel = tempStr;
			LoadTilegrid(fileName);
			LevelTime.restart();
		}
	}
	else
	{
		isNewLevel = false;
		isPlayerDead = false;
	}
}

void Tilegrid::LoadTilegrid(std::string FileName)
{
	std::cerr << "Load" << std::endl;
	std::ifstream inFile;
   	char f;
   	bool ReadingTileInfo = true;
   	bool ReadingString = true;
   	bool RectSet = false;
   	std::string info = "";
   	std::string fileName = "";
   	std::string tileSet;
   	int i = 0;
   	int tileImNr = 0;
   	bool tileCol = false;
   	char digit[3] = "";
   	char file[80] = "";

   	for(int j=0; j<FileName.length(); j++)
   		file[j] = FileName.at(j);

   	inFile.open(file);
   	if(!inFile)
   	{
   		std::cerr << file << " kunde inte hittas." << std::endl;
   		GameEngine::Stop();
   	}

   	while(inFile >> f)
   	{
   		info += f;
   	}

   	char infoC[info.length()];

   	for(int j=0; j<info.length(); j++)
   		infoC[j]=info.at(j);

   	{
   		int temp = 0;
		while(ReadingString)
		{
			if(info.at(i) == '"')
			{
				temp++;
				if(temp == 2)
				{
					ReadingString = false;
				}
			}
			else if(temp == 1)
			{
				tileSet += info.at(i);
			}

			i++;
		}
   	}

	if(!TileSet.loadFromFile(tileSet))
   	{
   		std::cerr << tileSet << " not found." << std::endl;
   		GameEngine::Stop();
   	}

   	{
   		int start = i;
   		while(!isdigit(infoC[start]))
   		{
   			i++;
   			start++;
   		}
   		int tempI;
   		tempI = start;

   		while(isdigit(infoC[tempI]))
   		{
   			tempI++;
   		}
   		int end = tempI;

   		for(int n=start; n<end; n++)
   		{
   			digit[n-start] += infoC[n];
   		}
   		i += (end-start);
   		LevelWidth = atoi(digit);
   	}

   	for(int n=2; n>=0; n--)
   		digit[n] = '\0';

   	{
   	   	int start = i;
   	   	while(!isdigit(infoC[start]))
   	   	{
   	   		i++;
   	 		start++;
   	   	}
   	   	int tempI;
   	   	tempI = start;

   	   	while(isdigit(infoC[tempI]))
   	   	{
   	   		tempI++;
   	   	}
   	   	int end = tempI;

   	   	for(int n=start; n<end; n++)
   	   	{
   	   		digit[n-start] += infoC[n];
   	   	}

   	   	i += (end-start);
   	   	LevelHeight = atoi(digit);
   	}

   	for(int n=2; n>=0; n--)
   	   	digit[n] = '\0';

   	{
   	   	int start = i;
   	   	while(!isdigit(infoC[start]))
   	   	{
   	  		i++;
   	 		start++;
   	   	}
   	   	int tempI;
   	   	tempI = start;

   	   	while(isdigit(infoC[tempI]))
   	   	{
   	   		tempI++;
   	   	}
   	   	int end = tempI;

   	   	for(int n=start; n<end; n++)
   	   	{
   	   		digit[n-start] += infoC[n];
   	   	}

   	   	i += (end-start);
   	   	PlayerNewX = (float)atoi(digit);
   	}

   	for(int n=2; n>=0; n--)
   	   	digit[n] = '\0';

   	{
   	   	int start = i;
   	   	while(!isdigit(infoC[start]))
   	   	{
   	  		i++;
   	 		start++;
   	   	}
   	   	int tempI;
   	   	tempI = start;

   	   	while(isdigit(infoC[tempI]))
   	  	{
   	  		tempI++;
   	   	}
   	   	int end = tempI;

   	   	for(int n=start; n<end; n++)
   	   	{
   	   		digit[n-start] += infoC[n];
   	   	}

   	   	i += (end-start);
   	   	PlayerNewY = (float)atoi(digit);
   	}

   	for(int n=2; n>=0; n--)
   	   	digit[n] = '\0';

   	{
   	   	int start = i;
   	  	while(!isdigit(infoC[start]))
   	   	{
   	  		i++;
   	 		start++;
   	   	}
   	   	int tempI;
   	   	tempI = start;

   	   	while(isdigit(infoC[tempI]))
   	  	{
   	   		tempI++;
   	   	}
   	   	int end = tempI;

   	   	for(int n=start; n<end; n++)
   	   	{
   	   		digit[n-start] += infoC[n];
   	   	}

   	  	i += (end-start);
   	  	TimeLimit = atoi(digit);
   	}

   	for(int n=2; n>=0; n--)
   		digit[n] = '\0';

   	for(int n=0; n<LevelHeight; n++)
   	{
   	   	std::vector<Tile> newVector;
   	    level.push_back(newVector);
   	}

   	for(int j=0; j<LevelHeight; j++)
   	{
        for(int k=0; k<LevelWidth; k++)
   		{
   			ReadingString = false;
   			ReadingTileInfo = true;
   			RectSet = false;

   			while(ReadingTileInfo)
   			{
   				if(info.at(i) == '<')
   				{
   					ReadingTileInfo = true;
   				}
   				if(info.at(i) == '>')
   				{
   					ReadingTileInfo = false;
   				}
				if(info.at(i) == '"' && ReadingString)
   				{
    				ReadingString = false;
    			}
    			else if(info.at(i) == '"' && !ReadingString)
    			{
    				ReadingString = true;
   				}

   				if(isdigit(infoC[i]))
   				{
   					int tempI;
   					int start = i;
   					tempI = start;

   					while(isdigit(infoC[tempI]))
   					{
   						tempI++;
   					}
   					int end = tempI;

   					for(int n=start; n<end; n++)
   					{
   						digit[n-start] += infoC[n];
   					}
   					i += (end-start-1);

   					if(RectSet == false)
   					{
   						tileImNr = atoi(digit);
   						RectSet = true;
   					}
   					else
   					{
   						tileCol = (bool)atoi(digit);
   					}
   				}

   				if(ReadingString)
   				{
   					i++;
   					int start = i;
   					int tempI = start;

   					while(info.at(tempI) != '"')
   					{
    					tempI++;
    				}
    				int end = tempI;

    				fileName = info.substr(start, end-start);
   					i += (end-start-1);
   				}

    			if(ReadingTileInfo && !ReadingString)
    			{
    				digit[2] = '\0';
    				digit[1] = '\0';
    				digit[0] = '\0';
    			}
    			i++;
   			}
    		Tile TempTile(tileImNr, tileCol, fileName, sf::Vector2u(TileSet.getSize().x / GameEngine::TILE_WIDTH, TileSet.getSize().y / GameEngine::TILE_HEIGHT));
    		level[j].push_back(TempTile);
    	}
   	}

   	TileSet.setSmooth(false);
   	sprite.setTexture(TileSet);

   	inFile.close();

   	SpawnNPCs();
}

void Tilegrid::SpawnNPCs()
{
	std::string tempStr;
	std::stringstream id;

	DeleteNPCs();

	for(int x=0; x<LevelWidth; x++)
	{
		for(int y=0; y<LevelHeight; y++)
		{
			tempStr = level[y][x].GetFileName();

			if(tempStr.length() > 6 && tempStr.substr(0,5) == "Spawn" && tempStr.substr(6, 3) == "npc")
			{
				std::string spawnString;

				id.str(std::string());
				id << npcs.size();

				spawnString = tempStr.substr(12, tempStr.length());
				NPC* tmpNPC = new NPC(x*GameEngine::TILE_WIDTH, y*GameEngine::TILE_HEIGHT, id.str(), 1.0f);

				npcs.push_back(tmpNPC);
			}
		}
	}
}

void Tilegrid::DeleteNPCs()
{
	for(int i=npcs.size()-1; i>=0; i--)
	{
		delete npcs.at(i);
		npcs.pop_back();
	}
}

void Tilegrid::UpdateNPCs()
{
	for(int i=0; i<npcs.size(); i++)
	{
		bool CanMove[4] = {IsAccessible(npcs.at(i)->GetX(), npcs.at(i)->GetY() - npcs.at(i)->GetYSpeed(), npcs.at(i)->GetWidth(), npcs.at(i)->GetHeight(), npcs.at(i)->GetId()),
						   IsAccessible(npcs.at(i)->GetX() + npcs.at(i)->GetXSpeed(), npcs.at(i)->GetY(), npcs.at(i)->GetWidth(), npcs.at(i)->GetHeight(), npcs.at(i)->GetId()),
						   IsAccessible(npcs.at(i)->GetX(), npcs.at(i)->GetY() + npcs.at(i)->GetYSpeed(), npcs.at(i)->GetWidth(), npcs.at(i)->GetHeight(), npcs.at(i)->GetId()),
						   IsAccessible(npcs.at(i)->GetX() - npcs.at(i)->GetXSpeed(), npcs.at(i)->GetY(), npcs.at(i)->GetWidth(), npcs.at(i)->GetHeight(), npcs.at(i)->GetId())
					      };

		npcs.at(i)->AI(CanMove);
		npcs.at(i)->update();
	}
}


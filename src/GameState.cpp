#include "GameState.h"
#include "GameEngine.h"

GameState::GameState() : GameView(sf::FloatRect(0, 0, GameEngine::WINDOW_WIDTH, GameEngine::WINDOW_HEIGHT))
{
    std::cerr << "Entering GameState" << std::endl;
		
	game.GetPlayer().SetX(game.GetTilegrid().GetNewX());
	game.GetPlayer().SetY(game.GetTilegrid().GetNewY());
	//game.GetPlayer().GetAnimated().SetPosition(game.GetPlayer().GetX(), game.GetPlayer().GetY());

	GameView.setCenter(game.GetPlayer().GetX(), game.GetPlayer().GetY());
	GameEngine::gEngine.FrameTexture.setView(GameView);
	GameEngine::gEngine.App.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
	
	Paused = false;
}

GameState::~GameState()
{
}

void GameState::Process()
{
    //std::cerr << "GameState: process" << std::endl;

    GameEngine::gEngine.App.pollEvent(event);

    bool LeftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool RightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool DownKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool LShiftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    bool EKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
	
	if(!Paused && !IsNewLevel)
	{
		if(LeftKeyDown)
		{
		    game.GetPlayer().movePlayerLeft(game.GetTilegrid().IsAccessible(game.GetPlayer().GetX()-game.GetPlayer().GetPlayerXSpeed(), game.GetPlayer().GetY(), GameEngine::PLAYER_WIDTH, GameEngine::PLAYER_HEIGHT, game.GetPlayer().GetId()));
		}
		else if(RightKeyDown)
		{
		    game.GetPlayer().movePlayerRight(game.GetTilegrid().IsAccessible(game.GetPlayer().GetX()+game.GetPlayer().GetPlayerXSpeed(), game.GetPlayer().GetY(), GameEngine::PLAYER_WIDTH, GameEngine::PLAYER_HEIGHT, game.GetPlayer().GetId()));
		}
		else if(UpKeyDown)
		{
		    game.GetPlayer().movePlayerUp(game.GetTilegrid().IsAccessible(game.GetPlayer().GetX(), game.GetPlayer().GetY()-game.GetPlayer().GetPlayerYSpeed(), GameEngine::PLAYER_WIDTH, GameEngine::PLAYER_HEIGHT, game.GetPlayer().GetId()));
		}
		else if(DownKeyDown)
		{
		    game.GetPlayer().movePlayerDown(game.GetTilegrid().IsAccessible(game.GetPlayer().GetX(), game.GetPlayer().GetY()+game.GetPlayer().GetPlayerYSpeed(), GameEngine::PLAYER_WIDTH, GameEngine::PLAYER_HEIGHT, game.GetPlayer().GetId()));
		}
		else
		    game.GetPlayer().stop();
    }
    
    State::Process();
}

void GameState::Update()
{
	//std::cerr << "GameState: update" << std::endl;
	
	game.GetTilegrid().UpdateTilegrid(game.GetPlayer().GetX(), game.GetPlayer().GetY());
		
	IsNewLevel = game.GetTilegrid().IsNewLevel();
	IsPlayerDead = game.GetTilegrid().IsPlayerDead();

	if(IsPlayerDead)
	{
		game.GetPlayer().Death();
	}
	if(IsNewLevel)
	{
		game.GetPlayer().SetX(game.GetTilegrid().GetNewX());
		game.GetPlayer().SetY(game.GetTilegrid().GetNewY());
	}


	//Stanna Viewen om hela banan �r mindre �n sk�rmen.
    if((game.GetTilegrid().GetLevelHeight() < (GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)) && (game.GetTilegrid().GetLevelWidth() < (GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)))
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=false;
    }

    //Stanna Viewen om banans bredd �r mindre �n sk�rmens bredd.
    else if(game.GetTilegrid().GetLevelWidth() < (GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH))
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=false;
    }

    //Stanna Viewen om banans h�jd �r mindre �n sk�rmens h�jd.
    else if(game.GetTilegrid().GetLevelHeight() < (GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT))
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=false;
    }

    //Stanna Viewen om b�de �verkant och v�nsterkant kan ses samtidigt.
    else if((((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) < ((GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2)) && ((game.GetPlayer().GetY()/GameEngine::TILE_HEIGHT) < ((GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2)))
    {
        NearBorder[0]=true;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=true;
    }

    //Stanna Viewen om b�de nederkant och h�gerkant kan ses samtidigt.
    else if((((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) >= (game.GetTilegrid().GetLevelWidth()-((GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2))) && (((game.GetPlayer().GetY())/GameEngine::TILE_HEIGHT) >= (game.GetTilegrid().GetLevelHeight()-((GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2))))
    {
        NearBorder[0]=false;
        NearBorder[1]=true;
        NearBorder[2]=true;
        NearBorder[3]=false;
    }

    //Stanna Viewen om b�de �verkant och h�gerkant kan ses samtidigt.
    else if(((game.GetPlayer().GetY()/GameEngine::TILE_HEIGHT) < (GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2) && (((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) >= (game.GetTilegrid().GetLevelWidth()-((GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2))))
    {
        NearBorder[0]=true;
        NearBorder[1]=false;
        NearBorder[2]=true;
        NearBorder[3]=false;
    }

    //Stanna Viewen om b�de nederkant och v�nsterkant kan ses samtidigt.
    else if((((game.GetPlayer().GetY())/GameEngine::TILE_HEIGHT) >= (game.GetTilegrid().GetLevelHeight()-((GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2))) && (((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) < (GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2))
    {
        NearBorder[0]=false;
        NearBorder[1]=true;
        NearBorder[2]=false;
        NearBorder[3]=true;
    }

    //Stanna Viewen om bara v�nsterkanten kan ses.
    else if(((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) < (GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2)
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=true;
    }

    //Stanna Viewen om bara �verkanten kan ses.
    else if((game.GetPlayer().GetY()/GameEngine::TILE_HEIGHT) < (GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2)
    {
        NearBorder[0]=true;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=false;

    }

    //Stanna Viewen om bara h�gerkanten kan ses.
    else if(((game.GetPlayer().GetX())/GameEngine::TILE_WIDTH) >= (game.GetTilegrid().GetLevelWidth()-((GameEngine::WINDOW_WIDTH/GameEngine::TILE_WIDTH)/2)))
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=true;
        NearBorder[3]=false;
    }

    //Stanna Viewen om bara nederkanten kan ses.
    else if(((game.GetPlayer().GetY())/GameEngine::TILE_HEIGHT) >= (game.GetTilegrid().GetLevelHeight()-((GameEngine::WINDOW_HEIGHT/GameEngine::TILE_HEIGHT)/2)))
    {
        NearBorder[0]=false;
        NearBorder[1]=true;
        NearBorder[2]=false;
        NearBorder[3]=false;
    }

    //Om ingen kant syns, flytta Viewen centrerad till spelaren.
    else
    {
        NearBorder[0]=false;
        NearBorder[1]=false;
        NearBorder[2]=false;
        NearBorder[3]=false;
    }
    GameView.setCenter(game.GetPlayer().GetX(), game.GetPlayer().GetY());

	if(!Paused && !IsNewLevel)
	{
		game.GetPlayer().update();
		game.GetTilegrid().UpdateNPCs();
	}
}

void GameState::Render() 
{
	if(IsNewLevel)
	{
		int opa = 0;
		
		sf::RectangleShape fadebox(sf::Vector2f(GameEngine::gEngine.FrameTexture.getSize().x*2, GameEngine::gEngine.FrameTexture.getSize().y*2));
		fadebox.setFillColor(sf::Color(0,0,0,255));
		GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
		
		while (opa <= 255)
		{
			fadebox.setFillColor(sf::Color(0,0,0, opa));
			GameEngine::gEngine.FrameTexture.draw(fadebox);
			GameEngine::gEngine.FrameTexture.display();
			
			//GameEngine::gEngine.PostFxShader.setParameter("timer", GameEngine::gEngine.shaderClock.getElapsedTime().asSeconds()*100);
			FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
			GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
			GameEngine::gEngine.App.display();
			opa += 600 * GameEngine::gEngine.GetFrameTime();
		}
		opa = 255;
		
		while (opa >= 0)
		{
			State::Render();
			GameEngine::gEngine.FrameTexture.setView(GameView);
			// Draw all tiles
			game.GetTilegrid().Render(game.GetPlayer(), NearBorder);
			GameEngine::gEngine.FrameTexture.draw(game.GetPlayer().GetAnimation());
			
			// Draw stats
			//GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
			//GameEngine::gEngine.FrameTexture.draw(game.GetPlayer().GetStatsString());
			//GameEngine::gEngine.FrameTexture.draw(game.GetTilegrid().GetTimeString());
			//GameEngine::gEngine.FrameTexture.setView(GameView);
			
			GameEngine::gEngine.FrameTexture.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
			
			fadebox.setFillColor(sf::Color(0,0,0, opa));
			// Draw fadebox
			GameEngine::gEngine.FrameTexture.draw(fadebox);
			GameEngine::gEngine.FrameTexture.display();
			
			//GameEngine::gEngine.PostFxShader.setParameter("timer", GameEngine::gEngine.shaderClock.getElapsedTime().asSeconds()*100);
			FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
			GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
			GameEngine::gEngine.App.display();
			
			opa -= 600 * GameEngine::gEngine.GetFrameTime();
		}
		GameEngine::gEngine.FrameTexture.setView(GameView);
	}
	else
	{
		//std::cerr << "GameState: render" << std::endl;
		State::Render();
		GameEngine::gEngine.FrameTexture.setView(GameView);
		game.GetTilegrid().Render(game.GetPlayer(), NearBorder);
		GameEngine::gEngine.FrameTexture.draw(game.GetPlayer().GetAnimation());
		GameEngine::gEngine.FrameTexture.display();
		
		//GameEngine::gEngine.PostFxShader.setParameter("timer", GameEngine::gEngine.shaderClock.getElapsedTime().asSeconds()*100);
		GameEngine::gEngine.App.setView(GameEngine::gEngine.FrameTexture.getDefaultView());
		FrameSprite.setTexture(GameEngine::gEngine.FrameTexture.getTexture());
		GameEngine::gEngine.App.draw(FrameSprite, &GameEngine::gEngine.PostFxShader);
		GameEngine::gEngine.App.display();
	}
}


// SDL Framework.cpp : 

#include "GameManager.h"

using SDLFramework::GameManager;



int main(int argc, char* args[])
{
	GameManager* game = GameManager::Instance();

	game->Run(); //Debug colliders shown/unshown is stored within Collider.h

	GameManager::Release();
	game = nullptr;	

	return 0;
    
}


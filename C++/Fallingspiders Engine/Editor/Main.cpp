#include <iostream>

#include <Game.h>

#include "DebugSystem.h"
#include "SceneSystem.h"

using namespace SpidersEngine;

Game* game = nullptr;


int main(int argc, char* args[])
{
	try
	{
		game = new Game();
		game->init(
			"Fallingspiders", 
			Game::N_CHUNKS_X * Game::PIXEL_SIZE * Game::CHUNK_SIZE,
			Game::N_CHUNKS_Y * Game::PIXEL_SIZE * Game::CHUNK_SIZE,
			false);

		game->addSystem(new DebugSystem("Debug System"));
		game->addSystem(new SceneSystem("Scene System"));

		game->loop();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
	}
	
	return 0;
}
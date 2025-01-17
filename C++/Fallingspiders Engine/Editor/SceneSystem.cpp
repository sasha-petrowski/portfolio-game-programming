#include "SceneSystem.h"

#include <Voxel.h>
#include <DefaultVoxels.h>
#include <World.h>
#include <Input.h>
#include <Random.h>

using namespace SpidersEngine;

void SceneSystem::create()
{
	//fill world
	for (int x = 0; x < Game::WORLD_WIDTH; x++)
	{
		for (int y = 0; y < Game::WORLD_HEIGHT / 16; y++)
		{
			world->replaceVoxel(x, Game::WORLD_WIDTH / 2 + y, Defaults::Wood);
		}
	}
}

void SceneSystem::start()
{
	std::cout << name << " has been started\n";
}

void SceneSystem::update()
{
	int rand = (Random::RandInt(Game::WORLD_WIDTH) + Random::RandInt(Game::WORLD_WIDTH)) / 2;
	Voxel* other = world->getVoxel(rand, Game::WORLD_HEIGHT * 0.45f);
	if(other && other->data->type == GAS) world->replaceVoxel(rand, Game::WORLD_HEIGHT * 0.45f, Defaults::Hydrogen);

	world->replaceVoxel(Game::WORLD_WIDTH * 0.2f, 0, Defaults::Gravel);
	world->replaceVoxel(Game::WORLD_WIDTH * 0.50f, 0, Defaults::Dirt);
	world->replaceVoxel(Game::WORLD_WIDTH * 0.8f, 0, Defaults::Sand);

	if (Game::getFrame() % 2 == 0)
	{
		world->replaceVoxel(Game::WORLD_WIDTH * .30f, 0, Defaults::Oil);
		world->replaceVoxel(Game::WORLD_WIDTH * .70f, 0, Defaults::Oil);
	}
	else
	{
		world->replaceVoxel(Game::WORLD_WIDTH * .30f, 0, Defaults::Water);
		world->replaceVoxel(Game::WORLD_WIDTH * .70f, 0, Defaults::Water);
	}

	VoxelData* lineData = nullptr;
	if (Input::mouseDown[SDL_BUTTON_LEFT]) lineData = Defaults::Fire;
	else
	if (Input::mouseDown[SDL_BUTTON_RIGHT]) lineData = Defaults::Air;
	else
	if (Input::mouseDown[SDL_BUTTON_MIDDLE]) lineData = Defaults::Sand;
	
	if(lineData) Voxel::SetLine(Input::mouseX - Input::relativeX, Input::mouseX, Input::mouseY - Input::relativeY, Input::mouseY, lineData, world);
}

void SceneSystem::debug()
{
}

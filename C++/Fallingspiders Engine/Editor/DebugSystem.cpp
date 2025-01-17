#include "DebugSystem.h"

#include <Voxel.h>
#include <World.h>
#include <Input.h>

using namespace SpidersEngine;

void DebugSystem::create()
{
	std::cout << name << " has been created\n";
}

void DebugSystem::start()
{
	std::cout << name << " has been started\n";
}

void DebugSystem::update()
{
}

void DebugSystem::debug()
{
	Voxel* newMouseVoxel = world->getVoxel(Input::mouseX, Input::mouseY);
	if (mMouseVoxel != newMouseVoxel && newMouseVoxel != nullptr)
	{
		if (mMouseVoxel && mMouseVoxel->debugFlag == true) mMouseVoxel->debugFlag = false;
		newMouseVoxel->debugFlag = true;

		mMouseVoxel = newMouseVoxel;
		std::cout << "Mouse state : P.[" << Input::mouseX << ", " << Input::mouseY << "] R.[" << Input::relativeX << ", " << Input::relativeY << "]\nHover : " << mMouseVoxel << "\n";
	}
}

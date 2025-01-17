#pragma once
#include <GameSystem.h>

using namespace SpidersEngine;

class DebugSystem : public GameSystem
{
public:
	DebugSystem(const char* name) : GameSystem(name) {}

protected:
	void create();
	void start();
	void update();
	void debug();


private:
	Voxel* mMouseVoxel;
};


#pragma once
#include <GameSystem.h>

using namespace SpidersEngine;

class SceneSystem : public GameSystem
{
public:
	SceneSystem(const char* name) : GameSystem(name) {}

protected:
	void create();
	void start();
	void update();
	void debug();
};


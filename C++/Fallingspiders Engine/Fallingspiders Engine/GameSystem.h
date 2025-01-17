#pragma once
#include "GameObject.h"

namespace SpidersEngine
{
	class GameSystem : public GameObject
	{
		friend class Game;

	public:
		GameSystem(const char* name) : GameObject(name) {}

	protected:
		virtual void start() = 0;
		virtual void update() = 0;
		virtual void debug() = 0;
	};
}


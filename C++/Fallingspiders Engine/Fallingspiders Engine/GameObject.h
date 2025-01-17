#pragma once
#include "World.h"

namespace SpidersEngine
{
	class GameObject
	{
		friend class Game;

	public:
		const char* name;
		World* world;

		GameObject(const char* name)
		{
			this->name = name;
		}

	protected:
		virtual void create() = 0;
	};
}


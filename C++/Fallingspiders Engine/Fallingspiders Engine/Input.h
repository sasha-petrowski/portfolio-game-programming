#pragma once
#include "Voxel.h"
#include "Game.h"
#include <queue>

namespace SpidersEngine
{
	static class Input
	{
		friend class Game;

		static const int KEYBOARD_SIZE = 322;
		static const int MOUSE_SIZE = 6;

	public:

		static int mouseX;
		static int mouseY;
		static int relativeX;
		static int relativeY;

		static bool keyPressed[KEYBOARD_SIZE];  // 322 is the number of SDLK_DOWN events
		static bool keyDown[KEYBOARD_SIZE];  // 322 is the number of SDLK_DOWN events

		static bool mousePressed[MOUSE_SIZE];  // 322 is the number of SDLK_DOWN events
		static bool mouseDown[MOUSE_SIZE];  // 322 is the number of SDLK_DOWN events

		static void initInputs();
		static bool handleEvents();

	private:
	};
}


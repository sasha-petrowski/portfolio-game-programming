#pragma once
#include <iostream>
#include "GameSystem.h"

namespace SpidersEngine
{
	static class Game
	{
	public:

		const static int CHUNK_SIZE = 32;
		const static int N_CHUNKS_X = 6;
		const static int N_CHUNKS_Y = 6;

		const static int PIXEL_SIZE = 5;

		const static int WORLD_WIDTH = N_CHUNKS_X * CHUNK_SIZE;
		const static int WORLD_HEIGHT = N_CHUNKS_Y * CHUNK_SIZE;

		const static int UPS = 60;
		const static int UPDATE_DELAY = 1000 / UPS;

		static void init(const char* title, int width, int height, bool fullscreen);
		static void initDefaults();
		static void loop();

		static void addSystem(GameSystem* system);

		static bool isRunning();
		static int getFrame();

	private:
		static void handleEvents();

		static void systemDebug();
		static void systemUpdate();
		static void voxelUpdate();
		static void physicsUpdate();

		static void render();
		static void clean();
	};

}

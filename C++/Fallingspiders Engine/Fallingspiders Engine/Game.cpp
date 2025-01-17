#include "Game.h"

#include "SDL.h"
#include "SDL_image.h"

#include "DefaultVoxels.h"
#include "Input.h"
#include "World.h"

namespace SpidersEngine
{
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	World* mWorld;

	bool mIsRunning;
	bool mIsPaused;

	uint32_t mFrameCount;

	std::vector<GameSystem*>* mSystems;
	std::queue<GameSystem*>* mNewSystems;

	void Game::init(const char* title, int width, int height, bool fullscreen)
	{
		mIsRunning = false;
		mIsPaused = false;

		mSystems = new std::vector<GameSystem*>();
		mNewSystems = new std::queue<GameSystem*>();

#pragma region Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) return;
		std::cout << "SDL Initialized\n";
#pragma endregion
#pragma region Initialize mWindow
		int windowFlags = 0;
		if (fullscreen)
		{
			windowFlags = SDL_WINDOW_FULLSCREEN;
		}

		mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (!mWindow) return;

		std::cout << "Window Created\n";
#pragma endregion
#pragma region Initialize mRenderer

		mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

		if (!mRenderer) return;

		std::cout << "Renderer Created\n";

		SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(mRenderer, 55, 55, 55, 255);

#pragma endregion

		Input::initInputs();

		initDefaults();

		mWorld = new World(N_CHUNKS_X, N_CHUNKS_Y, CHUNK_SIZE, mRenderer);
		std::cout << "World created\n";

		mIsRunning = true;
		mFrameCount = 0;

	}

	void Game::loop()
	{
		if (!mIsRunning) return;

		Uint32 frameStart;
		Uint32 cycleStart = 0;
		int frameTime;

		while (mIsRunning)
		{
			frameStart = SDL_GetTicks();
			handleEvents();


			if (mIsPaused == false || Input::keyPressed['n'])	//Updates
			{
				if (mFrameCount % UPS == 0)
				{
					float t = (frameStart - cycleStart) / (float)(UPDATE_DELAY * UPS);
					std::cout << "- - - - - - - - - - - - - -\nS." << mFrameCount / UPS << " [" << roundf(UPS * 10 / t) / 10 << "/" << UPS << "] UPS\n";
					cycleStart = frameStart;
				}
				systemDebug();
				systemUpdate();

				physicsUpdate();
				voxelUpdate();

				mFrameCount++;
				render();
			}

			frameTime = SDL_GetTicks() - frameStart;

			if (UPDATE_DELAY > frameTime)
			{
				SDL_Delay(roundf(UPDATE_DELAY - frameTime));
			}
		}

		clean();
	}

	void Game::addSystem(GameSystem* system)
	{
		mNewSystems->push(system);

		system->world = mWorld;
		system->create();
	}

	bool Game::isRunning() { return mIsRunning; }
	int Game::getFrame() { return mFrameCount; }

	void Game::handleEvents()
	{
		mIsRunning = Input::handleEvents();

		if (Input::keyPressed[SDLK_SPACE]) mIsPaused = !mIsPaused;
	}

	void Game::systemDebug()
	{
		for (GameSystem* sys : *mSystems)
		{
			sys->debug();
		}
	}

	void Game::systemUpdate()
	{
		while (!mNewSystems->empty()) //Call the start method on new systems before anything else is updated this frame
		{
			mSystems->push_back(mNewSystems->front());
			mNewSystems->front()->start();
			mNewSystems->pop();
		}

		for(GameSystem* sys : *mSystems)
		{
			sys->update();
		}
	}

	void Game::voxelUpdate()
	{
		mWorld->updateChunks();
	}

	void Game::physicsUpdate()
	{
	}
	void Game::render()
	{
		SDL_RenderClear(mRenderer);

		//SDL_RenderCopy(mRenderer, testTex, nullptr, nullptr);
		mWorld->renderCopy(mRenderer);

		SDL_RenderPresent(mRenderer);
	}

	void Game::clean()
	{
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		SDL_Quit();

		std::cout << "Game Cleaned\n";
	}

}

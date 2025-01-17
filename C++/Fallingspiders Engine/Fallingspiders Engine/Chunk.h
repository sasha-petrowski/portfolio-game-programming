#pragma once
#include <queue>

#include "Voxel.h"
#include "SDL.h"

namespace SpidersEngine
{
	class Voxel;
	class VoxelData;

	class Chunk
	{
	public:
		SDL_Texture* DevDirtyTexture;
		SDL_Texture* DevDebugTexture;
		SDL_Rect* renderRect;

		std::vector<Voxel*> Voxels;

		Chunk(int x, int y, int width, int height, SDL_Renderer* renderer, Cluster* cluster);
		~Chunk();

		void prepareUpdate();
		void updateTexture();
		void updateDebugTexture();
		void updateBackground();
		void updateVoxels();

		SDL_Texture* getTexture();
		void renderCopy(SDL_Renderer* renderer);

		void wakeVoxel(int i);
		void dirtyVoxel(int x, int y);

		int getWidth() { return mWidth; }
		int getHeight() { return mHeight; }
	private:
		SDL_Texture* mTexture;
		SDL_Texture* mBackgroundTexture;

		std::queue<Voxel*>* mUpdateQueue = new std::queue<Voxel*>();
		std::queue<Voxel*>* mCachedQueue = new std::queue<Voxel*>();

		std::vector<uint32_t> mBackground;

		int mWorldX;
		int mWorldY;

		int mDirtyMinX;
		int mDirtyMinY;
		int mDirtyMaxX;
		int mDirtyMaxY;

		int mWidth, mHeight;

		bool mIsDirty;
	};
}


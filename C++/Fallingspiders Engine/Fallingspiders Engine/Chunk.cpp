#include "Chunk.h"

#include "Game.h"
#include "Input.h"
#include "Random.h"
#include "Cluster.h"
#include "DefaultVoxels.h"

#include "NoisyHexagonTemplate.h"
#include "TiledBackgroundTemplate.h"


namespace SpidersEngine
{

	Chunk::Chunk(int x, int y, int width, int height, SDL_Renderer* renderer, Cluster* cluster)
	{
		this->mWorldX = x;
		this->mWorldY = y;

		this->mWidth = width;
		this->mHeight = height;

#pragma region Setup renderRect
		this->renderRect = new SDL_Rect();

		renderRect->x = x * Game::PIXEL_SIZE;
		renderRect->y = y * Game::PIXEL_SIZE;
		renderRect->w = width * Game::PIXEL_SIZE;
		renderRect->h = height * Game::PIXEL_SIZE;

		mDirtyMinX = 0;
		mDirtyMinY = 0;
		mDirtyMaxX = width  - 1;
		mDirtyMaxY = height - 1;
#pragma endregion

		mBackgroundTexture = SDL_CreateTexture(renderer,
			Defaults::PixelFormat->format,
			SDL_TEXTUREACCESS_STREAMING,
			height,
			width);
		SDL_SetTextureBlendMode(mBackgroundTexture, SDL_BLENDMODE_BLEND);

		mTexture = SDL_CreateTexture(renderer,
			Defaults::PixelFormat->format,
			SDL_TEXTUREACCESS_STREAMING,
			height,
			width);
		SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);

		DevDirtyTexture = SDL_CreateTexture(renderer,
			Defaults::PixelFormat->format,
			SDL_TEXTUREACCESS_STREAMING,
			height,
			width);
		SDL_SetTextureBlendMode(DevDirtyTexture, SDL_BLENDMODE_BLEND);

		DevDebugTexture = SDL_CreateTexture(renderer,
			Defaults::PixelFormat->format,
			SDL_TEXTUREACCESS_STREAMING,
			height,
			width);
		SDL_SetTextureBlendMode(DevDebugTexture, SDL_BLENDMODE_BLEND);

#pragma region Initialize Voxels
		Voxels.resize(width * height);
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				Voxels[y * mWidth + x] = new Voxel(x + this->mWorldX, y + this->mWorldY, cluster, Defaults::Air);
			}
		}
#pragma endregion

#pragma region Initialize Voxels
		ColorTemplate* backgroundTemplate = new NoisyHexagonTemplate();

		mBackground.resize(width * height);
		for (int y = 0; y < mHeight; y++)
		{
			for (int x = 0; x < mWidth; x++)
			{
				mBackground[y * mWidth + x] = backgroundTemplate->GetColor(x + mWorldX, y + mWorldY);
			}
		}
#pragma endregion

		updateBackground();
		updateTexture();
	}

	Chunk::~Chunk()
	{
		Voxels.clear();
		mBackground.clear();
		delete mUpdateQueue;
		delete mCachedQueue;

		SDL_DestroyTexture(mBackgroundTexture);
		SDL_DestroyTexture(mTexture);
		SDL_DestroyTexture(DevDebugTexture);
		SDL_DestroyTexture(DevDirtyTexture);
	}

	void Chunk::prepareUpdate()
	{
		//swith current updateQueue and CachedQueue
		std::queue<Voxel*>* tmp = mUpdateQueue;
		mUpdateQueue = mCachedQueue;
		mCachedQueue = tmp;
	}

	void Chunk::updateTexture()
	{
		//std::cout << "Updating texture : [X1." << mDirtyMinX << " Y1." << mDirtyMinY << " X2." << mDirtyMaxX << " Y2." << mDirtyMaxY << "]\n";

		SDL_Rect* dirtyRect = new SDL_Rect();
		dirtyRect->x = mDirtyMinX;
		dirtyRect->y = mDirtyMinY;
		dirtyRect->w = 1 + mDirtyMaxX - mDirtyMinX;
		dirtyRect->h = 1 + mDirtyMaxY - mDirtyMinY;

		Uint32* pixels = nullptr;
		Uint32* dirtyPixels = nullptr;
		int pitch = 0;

		if (SDL_LockTexture(mTexture, dirtyRect, (void**)&pixels, &pitch)) { throw(SDL_GetError()); }
		if (SDL_LockTexture(DevDirtyTexture, nullptr, (void**)&dirtyPixels, &pitch)) { throw(SDL_GetError()); }

#pragma region Clean Dev texs
		for (int i = 0; i < mWidth * mHeight; i++)
		{
			if (i % mWidth == 0 || i % mWidth == mWidth - 1 || i < mWidth || i > mWidth * mHeight - mWidth)
				dirtyPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 255, 255, 255, 25);
			else
				dirtyPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 0, 0, 0, 0);
		}
#pragma endregion

#pragma region Color dirty pixels
		for (int y = 0; y < dirtyRect->h; y++)
		{
			for (int x = 0; x < dirtyRect->w; x++)
			{
				int voxelPosition = (y + dirtyRect->y) * mWidth + (x + dirtyRect->x);
				int pixelPosition = y * mWidth + x;

				//if (mVoxels[pixelPosition]->isCopy) updatePixels[pixelPosition] = SDL_MapRGBA(Defaults::PixelFormat, 255, 0, 255, 255); 
				pixels[pixelPosition] = Voxels[voxelPosition]->color;

				if (voxelPosition % mWidth == 0 || voxelPosition % mWidth == mWidth - 1 || voxelPosition < mWidth || voxelPosition > mWidth * mHeight - mWidth)
				{
					dirtyPixels[voxelPosition] = SDL_MapRGBA(Defaults::PixelFormat, 255, 100, 100, 100);
				}
				else
				{
					dirtyPixels[voxelPosition] = SDL_MapRGBA(Defaults::PixelFormat, 255, 0, 0, 100);
				}
			}
		}
#pragma endregion


		SDL_UnlockTexture(mTexture);
		SDL_UnlockTexture(DevDirtyTexture);

		mIsDirty = false;
	}

	void Chunk::updateDebugTexture()
	{
		Uint32* debugPixels = nullptr;
		int pitch = 0;

		if (SDL_LockTexture(DevDebugTexture, nullptr, (void**)&debugPixels, &pitch)) { throw(SDL_GetError()); }

#pragma region Color updated voxels
		for (int i = 0; i < mWidth * mHeight; i++)
		{
			if (Voxels[i]->debugFlag == true)
			{
				debugPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 255, 0, 0, 255);
			}
			else if (Voxels[i]->behaviour && Voxels[i]->awake)
			{
				debugPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 0, 255, 0, 255);
			}
			else if (Voxels[i]->behaviour)
			{
				debugPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 255, 255, 255, 255);
			}
			else if (Voxels[i]->awake)
			{
				debugPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 0, 255, 0, 100);
			}
			else // clean
			{
				debugPixels[i] = SDL_MapRGBA(Defaults::PixelFormat, 0, 0, 0, 0);
			}
		}
#pragma endregion

		SDL_UnlockTexture(DevDebugTexture);
	}

	void Chunk::updateBackground()
	{
		Uint32* pixels = nullptr;
		int pitch = 0;

		if (SDL_LockTexture(mBackgroundTexture, nullptr, (void**)&pixels, &pitch)) { throw(SDL_GetError()); }

		for (int i = 0; i < mWidth * mHeight; i++)
		{
			pixels[i] = mBackground[i];
		}

		SDL_UnlockTexture(mBackgroundTexture);
	}

	void Chunk::updateVoxels()
	{
		if (mCachedQueue->empty()) return;

		Voxel* voxel = nullptr;
		while (!mCachedQueue->empty())
		{
			voxel = mCachedQueue->front();
			mCachedQueue->pop();

			if (voxel->awake == true)
			{
				voxel->awake = false;
			}
			else 
			{
				delete voxel; //if the voxel was not awake, it means it need to be destroyed
				continue;
			}

			if (voxel->behaviour)
			{
				voxel->behaviour->tick(voxel->x, voxel->y, voxel, voxel->cluster);
			}
			else if (voxel->data->logic)
			{
				voxel->data->logic->tick(voxel->x, voxel->y, voxel, voxel->cluster);
			}

			if (voxel->data->reactions)
			{
				Voxel* up = voxel->cluster->getVoxel(voxel->x, voxel->y - 1);
				Voxel* down = voxel->cluster->getVoxel(voxel->x, voxel->y + 1);
				Voxel* left = voxel->cluster->getVoxel(voxel->x - 1, voxel->y);
				Voxel* right = voxel->cluster->getVoxel(voxel->x + 1, voxel->y);

				for (VoxelReaction* reaction : *(voxel->data->reactions))
				{
					if (up && reaction->tryReact(voxel, up)) continue;
					if (down && reaction->tryReact(voxel, down)) continue;
					if (left && reaction->tryReact(voxel, left)) continue;
					if (right && reaction->tryReact(voxel, right)) continue;
				}
			}
		}
	}

	SDL_Texture* Chunk::getTexture()
	{
		if (mIsDirty) updateTexture();

		return mTexture;
	}

	void Chunk::renderCopy(SDL_Renderer* renderer)
	{
		bool wasDirty = mIsDirty;
		if (mIsDirty) updateTexture();

		SDL_RenderCopy(renderer, mBackgroundTexture, nullptr, renderRect);
		SDL_RenderCopy(renderer, mTexture, nullptr, renderRect);

		//if (wasDirty) SDL_RenderCopy(renderer, DevDirtyTexture, nullptr, renderRect);
		
		//updateDebugTexture();
		//SDL_RenderCopy(renderer, DevDebugTexture, nullptr, renderRect);
	}

	void Chunk::wakeVoxel(int i)
	{
		if (Voxels[i]->TryWake()) mUpdateQueue->push(Voxels[i]);
	}

	void Chunk::dirtyVoxel(int x, int y)
	{
		if (mIsDirty == false) // chunk was clean, so we reset the dirty rectangle at this position
		{
			mDirtyMinX = x;
			mDirtyMinY = y;
			mDirtyMaxX = x;
			mDirtyMaxY = y;
		}
		else  // chunk was NOT clean, so we extend the dirty rectangle towards the new voxel
		{
#pragma region Horizontal X axis
			if (mDirtyMinX > x) //x is left (negative)
			{
				mDirtyMinX = x;
			}
			else if (mDirtyMaxX < x) //x is right (positive)
			{
				mDirtyMaxX = x;
			}
			//else if x is inside, do nothing
#pragma endregion
#pragma region Vertical Y axis
			if (mDirtyMinY > y) //y is left (negative)
			{
				mDirtyMinY = y;
			}
			else if (mDirtyMaxY < y) //y is right (positive)
			{
				mDirtyMaxY = y;
			}
			//else if y is inside, do nothing
#pragma endregion
		}

		mIsDirty = true;
	}
}

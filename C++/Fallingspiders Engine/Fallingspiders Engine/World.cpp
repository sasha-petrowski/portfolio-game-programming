#include "World.h"
#include "DefaultVoxels.h"

namespace SpidersEngine
{
	World::World(int chunksX, int chunksY, int chunkSize, SDL_Renderer* renderer)
	{
		this->name = "World";

		this->mChunksX = chunksX;
		this->mChunksY = chunksY;

		this->mChunksize = chunkSize;

		this->mWidth = chunkSize * chunksX;
		this->mHeight = chunkSize * chunksY;

		mChunks.resize(mChunksX * mChunksY);
		for (int y = 0; y < chunksX; y++)
		{
			for (int x = 0; x < chunksY; x++)
			{
				mChunks[y * chunksX + x] = new Chunk(x * chunkSize, y * chunkSize, chunkSize, chunkSize, renderer, this);
			}
		}
	}
	World::~World()
	{

	}

	void World::wakeVoxel(int x, int y)
	{
		if (x < 0 || x >= mWidth || y < 0 || y >= mHeight) return;

		mChunks[y / mChunksize * mChunksX + x / mChunksize]->wakeVoxel(y % mChunksize * mChunksize + x % mChunksize);

		/*
		int chunkPosition = y / mChunksize * mWidth + x / mChunksize;
		int voxelPosition = y % mChunksize * mChunksize + x % mChunksize;

		mChunks[chunkPosition]->wakeVoxel(voxelPosition);
		*/
	}

	
	void World::setVoxel(int x, int y, Voxel* voxel)
	{
		// test if out of bounds
		if (x < 0 || x >= mWidth || y < 0 || y >= mHeight)
		{
			std::cout << "Err : SetVoxel out of bound\n";
			return;
		}

		//int chunkPosition = y / mChunksize * mChunksX + x / mChunksize;
		int voxelPosition = y % mChunksize * mChunksize + x % mChunksize;

		Chunk* chunk = mChunks[y / mChunksize * mChunksX + x / mChunksize];

		chunk->Voxels[voxelPosition] = voxel;

		voxel->x = x;
		voxel->y = y;

#pragma region Wake voxels
		//wake self
		chunk->wakeVoxel(voxelPosition);
		//wake neighbors (might not be in same chunk)
		wakeVoxel(x, y - 1);
		wakeVoxel(x, y + 1);
		wakeVoxel(x - 1, y);
		wakeVoxel(x + 1, y);
		wakeVoxel(x - 1, y + 1);
		wakeVoxel(x + 1, y - 1);
		wakeVoxel(x + 1, y + 1);
		wakeVoxel(x - 1, y - 1);
#pragma endregion

		chunk->dirtyVoxel(x % mChunksize, y % mChunksize);
	}

	void World::replaceVoxel(int x, int y, VoxelData* data)
	{
		Voxel* voxel = getVoxel(x, y);
		if (voxel)
		{
			//cleanup any behaviour
			if (voxel->behaviour)
			{
				delete voxel->behaviour;
				voxel->behaviour = nullptr;
			}
			voxel->isCopy = false;
			voxel->init(data);
			voxel->cluster->setVoxel(x, y, voxel);
		}
	}

	Voxel* World::getVoxel(int x, int y)
	{
		// test if out of bounds
		if (x < 0 || x >= mWidth || y < 0 || y >= mHeight) return nullptr;

		//int chunkPosition = y / mChunksize * mChunksX + x / mChunksize;
		//int voxelPosition = y % mChunksize * mChunksize + x % mChunksize;

		return mChunks[y / mChunksize * mChunksX + x / mChunksize]->Voxels[y % mChunksize * mChunksize + x % mChunksize];
	}

	void World::updateChunks()
	{
		for (int i = 0; i < mChunksX * mChunksY; i++)
		{
			mChunks[i]->prepareUpdate();
		}
		for (int i = 0; i < mChunksX * mChunksY; i++)
		{
			mChunks[i]->updateVoxels();
		}
	}

	void World::renderCopy(SDL_Renderer* renderer)
	{
		for (int i = 0; i < mChunksX * mChunksY; i++)
		{
			mChunks[i]->renderCopy(renderer);
		}
	}
}
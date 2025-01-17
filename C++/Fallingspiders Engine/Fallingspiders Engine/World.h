#pragma once
#include "Cluster.h"
#include "Chunk.h"

#include <vector>

namespace SpidersEngine
{
	class Chunk;
	class Cluster;

	class World : public Cluster
	{
	public:
		World(int chunksX, int chunksY, int chunkSize, SDL_Renderer* renderer);
		~World();

		void wakeVoxel(int x, int y);

		void setVoxel(int x, int y, Voxel* voxel);

		void replaceVoxel(int x, int y, VoxelData* data);

		Voxel* getVoxel(int x, int y);


		void updateChunks();

		void renderCopy(SDL_Renderer* renderer);

	private:
		std::vector<Chunk*> mChunks;

		int mChunksX;
		int mChunksY;
		int mChunksize;
		int mWidth;
		int mHeight;
	};
}
#pragma once
#include "Voxel.h"
#include "Cluster.h"

namespace SpidersEngine
{

	class Voxel;
	class Cluster;

	class VoxelLogic
	{
	public:
		VoxelData* data;
		int freefallPercentChance = 0;

		virtual void tick(int x, int y, Voxel* voxel, Cluster* cluster) = 0;
		virtual bool canGoTo(Voxel* other) = 0;

		void tryFree(int x, int y, int dirX, int vX, int vY, Cluster* cluster);
		void free(int vX, int vY, Voxel* voxel);

	};

}

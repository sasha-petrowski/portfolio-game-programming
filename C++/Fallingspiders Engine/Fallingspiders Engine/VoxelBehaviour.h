#pragma once
#include "Cluster.h"

namespace SpidersEngine
{
	class Voxel;
	class Cluster;

	class VoxelBehaviour
	{
	public:
		virtual void tick(int x, int y, Voxel* voxel, Cluster* cluster) = 0;
	};
}


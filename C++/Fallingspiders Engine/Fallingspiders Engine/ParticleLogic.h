
#pragma once
#include "VoxelLogic.h"

namespace SpidersEngine
{
	class ParticleLogic : public VoxelLogic
	{
	public:
		int lifetime;

		ParticleLogic(int lifetime);

		void tick(int x, int y, Voxel* voxel, Cluster* cluster);

		bool canGoTo(Voxel* other);
	};
}

#pragma once
#include "VoxelBehaviour.h"

#include "Voxel.h"
#include "Cluster.h"

namespace SpidersEngine
{
	class FreefallBehaviour : public VoxelBehaviour
	{
	public:
		float vX;
		float vY;

		FreefallBehaviour(int vX, int vY);

		void tick(int x, int y, Voxel* voxel, Cluster* world);
	};
}


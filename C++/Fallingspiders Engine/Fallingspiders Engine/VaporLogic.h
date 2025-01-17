
#pragma once
#include "VoxelLogic.h"

namespace SpidersEngine
{
	class VaporLogic : public VoxelLogic
	{
	public:
		int sidePercent;
		int trailtime;
		int lifetime;

		VaporLogic(int sidePercent, float trail, int lifetime);

		void tick(int x, int y, Voxel* voxel, Cluster* cluster);

		bool canGoTo(Voxel* other);
		//bool canGoY(Voxel* other, int dir);
	};
}

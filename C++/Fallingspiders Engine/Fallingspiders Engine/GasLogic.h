#pragma once
#include "VoxelLogic.h"

namespace SpidersEngine
{

	class GasLogic : public VoxelLogic
	{
	public:
		int sidePercent;


		GasLogic(int sidePercent);

		void tick(int x, int y, Voxel* voxel, Cluster* cluster);

		bool canGoTo(Voxel* other);
		//bool canGoY(Voxel* other, int dir);
	};
}

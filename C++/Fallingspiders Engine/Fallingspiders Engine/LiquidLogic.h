#pragma once
#include "VoxelLogic.h"

namespace SpidersEngine
{

	class LiquidLogic : public VoxelLogic
	{
	public:
		int gravityResistPercent;

		LiquidLogic(int freefallPercentChance = 0, int gravityResistPercent = 0);

		void tick(int x, int y, Voxel* voxel, Cluster* cluster);

		bool canGoTo(Voxel* other);
		//bool canGoY(Voxel* other, int dir);
	};

}

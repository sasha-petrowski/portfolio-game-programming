#pragma once
#include "VoxelReaction.h"

namespace SpidersEngine
{
	class BurnChanceReaction : public VoxelReaction
	{
	public:
		int burnChance;
		BurnChanceReaction(int burnChance);

		bool tryReact(Voxel* self, Voxel* other);

	protected:
		void react(Voxel* self, Voxel* other);
	};

}

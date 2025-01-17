#pragma once
#include "VoxelReaction.h"

namespace SpidersEngine
{
	class BurnReaction : public VoxelReaction
	{
	public:
		bool tryReact(Voxel* self, Voxel* other);

	protected:
		void react(Voxel* self, Voxel* other);
	};

}

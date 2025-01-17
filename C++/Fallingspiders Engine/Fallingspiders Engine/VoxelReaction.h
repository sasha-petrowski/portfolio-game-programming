#pragma once
#include "Voxel.h"

namespace SpidersEngine
{

	class Voxel;

	class VoxelReaction
	{
	public:
		virtual bool tryReact(Voxel* self, Voxel* other) = 0;

	protected:
		virtual void react(Voxel* self, Voxel* other) = 0;
	};

}

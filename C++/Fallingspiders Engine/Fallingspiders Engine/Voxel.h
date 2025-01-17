#pragma once
#include "VoxelData.h"
#include "VoxelBehaviour.h"
#include "Cluster.h"

#include <iostream>

namespace SpidersEngine
{

	class VoxelData;
	class VoxelBehaviour;
	class World;

	class Voxel
	{

	public:
		int x, y;
		uint32_t color;
		VoxelData* data;
		Cluster* cluster = nullptr;
		VoxelBehaviour* behaviour = nullptr;
		bool awake = false;
		bool isCopy = false;
		bool debugFlag = false;

		Voxel(int x, int y, Cluster* cluster, VoxelData* data);
		~Voxel();

		bool TryWake();

		void init(VoxelData* data);

		static void SetLine(int startX, int endX, int startY, int endY, VoxelData* data, Cluster* cluster);

	private:
	};
	
	std::ostream& operator<<(std::ostream& stream, const Voxel* voxel);
	
}

#pragma once

namespace SpidersEngine
{
	class Voxel;
	class VoxelData;

	class Cluster
	{
	public:
		const char* name;

		virtual void wakeVoxel(int x, int y) = 0;

		virtual void setVoxel(int x, int y, Voxel* voxel) = 0;

		virtual void replaceVoxel(int x, int y, VoxelData* data) = 0;

		virtual Voxel* getVoxel(int x, int y) = 0;
	};
}
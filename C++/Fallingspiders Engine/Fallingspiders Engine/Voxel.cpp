#include "Voxel.h"
#include "Random.h"
#include "DefaultVoxels.h"


namespace SpidersEngine
{
	Voxel::Voxel(int x, int y, Cluster* cluster, VoxelData* data)
	{
		this->x = x;
		this->y = y;

		this->cluster = cluster;

		init(data);
	}

	Voxel::~Voxel()
	{
		awake = false;
		if (behaviour != nullptr) delete behaviour;
	}

	bool Voxel::TryWake()
	{
		bool wasAwake = awake;
		awake = true;

		return !wasAwake; // return false if it was awake.
	}

	void Voxel::init(VoxelData* data)
	{
		this->data = data;

		color = data->colorTemplate->GetColor(x, y);
	}
	void Voxel::SetLine(int startX, int endX, int startY, int endY, VoxelData* data, Cluster* cluster)
	{
		if (startX == endX && startY == endY)
		{
			cluster->replaceVoxel(startX, startY, data);
			return;
		}

		float steps = fabsf(endX - startX) + fabsf(endY - startY);

		float t;
		int x;
		int y;

		for (int i = 0; i < steps; i++)
		{
			t = i / steps;
			x = roundf(startX + t * (endX - startX));
			y = roundf(startY + t * (endY - startY));

			cluster->replaceVoxel(x, y, data);
		}
	}

	std::ostream& operator<<(std::ostream& stream, const Voxel* voxel)
	{
		stream << voxel->data << " P.[" << voxel->x << ", " << voxel->y << "] C.[" << voxel->cluster->name << "]";
		if (voxel->isCopy)
		{
			stream << " Is Copy";
		}
		if (voxel->awake)
		{
			stream << " Awake [" << voxel->behaviour << "]";
		}

		return stream;
	}
}


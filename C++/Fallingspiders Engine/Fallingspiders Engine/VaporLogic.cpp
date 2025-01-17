#include "VaporLogic.h"

#include "Random.h"
#include "DefaultVoxels.h"

namespace SpidersEngine
{
	VaporLogic::VaporLogic(int sidePercent, float trail, int lifetime)
	{
		this->sidePercent = sidePercent;
		this->trailtime = lifetime / trail;
		this->lifetime = lifetime;
	}

	void VaporLogic::tick(int x, int y, Voxel* voxel, Cluster* cluster)
	{
		int rand = Random::RandInt();
		if (rand % lifetime == 0)
		{
			if (voxel->isCopy || !voxel->data->tryCool(voxel))
			{
				voxel->init(Defaults::Air);
				voxel->isCopy = false;
				voxel->cluster->setVoxel(voxel->x, voxel->y, voxel);
			}
			return;
		}

		rand = rand % 100;
		if (rand < sidePercent) // try to go sideways
		{
			int side = 1 - (rand % 2) * 2;

			Voxel* other = cluster->getVoxel(x + side, y);
			if (canGoTo(other))
			{
				if (voxel->isCopy == false && other->data == Defaults::Air && Random::RandInt() % trailtime == 0)
				{
					other->init(voxel->data);
					other->isCopy = true;
				}

				cluster->setVoxel(x + side, y, voxel);
				cluster->setVoxel(x, y, other);
				return;
			}
		}
		else // try to go up
		{
			Voxel* other = cluster->getVoxel(x, y - 1);
			if (canGoTo(other))
			{
				if (voxel->isCopy == false && other->data == Defaults::Air && Random::RandInt() % trailtime == 0)
				{
					other->init(voxel->data);
					other->isCopy = true;
				}

				cluster->setVoxel(x, y - 1, voxel);
				cluster->setVoxel(x, y, other);
				return;
			}
		}

		//Keep it awake until it returns to being a liquid
		cluster->wakeVoxel(x, y);
	}
	bool VaporLogic::canGoTo(Voxel* other)
	{
		return other && other->data->type == GAS && other->data->weight > data->weight;
	}
	/*
	bool VaporLogic::canGoY(Voxel* other, int dir)
	{
		return other && other->data->type == GAS && other->data->weight * dir < data->weight * dir;
	}
	*/
}

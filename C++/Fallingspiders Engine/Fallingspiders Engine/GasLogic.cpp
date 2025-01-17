#include "GasLogic.h"
#include "DefaultVoxels.h"
#include "Random.h"

SpidersEngine::GasLogic::GasLogic(int sidePercent)
{
	this->sidePercent = sidePercent;
}

void SpidersEngine::GasLogic::tick(int x, int y, Voxel* voxel, Cluster* cluster)
{
	int rand = Random::RandInt(100);
	if (rand < sidePercent) // try to go sideways
	{
		int side = 1 - (rand % 2) * 2;

		Voxel* other = cluster->getVoxel(x + side, y);
		if (canGoTo(other))
		{
			cluster->setVoxel(x + side, y, voxel);
			cluster->setVoxel(x, y, other);
			return;
		}
		//Keep it awake if it's still possible to move somewhere else
		//if (canGoTo(cluster->getVoxel(x - side, y)) || canGoY(cluster->getVoxel(x, y - 1), -1)) cluster->wakeVoxel(x, y);
		if (canGoTo(cluster->getVoxel(x - side, y))) cluster->wakeVoxel(x, y);
	}
	else // try to go up
	{
		Voxel* other = cluster->getVoxel(x, y - 1);
		//canGoY
		if (canGoTo(other))
		{
			cluster->setVoxel(x, y - 1, voxel);
			cluster->setVoxel(x, y, other);
			return;
		}
		//Keep it awake if it's still possible to move somewhere else
		if (canGoTo(cluster->getVoxel(x + 1, y)) || canGoTo(cluster->getVoxel(x - 1, y))) cluster->wakeVoxel(x, y);
	}
}

bool SpidersEngine::GasLogic::canGoTo(Voxel* other)
{
	return other && other->data->type == GAS && other->data->weight > data->weight;
}
/*
bool SpidersEngine::GasLogic::canGoY(Voxel* other, int dir)
{
	return other && other->data->type == GAS && other->data->weight * dir < data->weight * dir;
}
*/

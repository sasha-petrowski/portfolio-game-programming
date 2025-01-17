#include "VoxelLogic.h"

#include "Random.h"

#include "FreefallBehaviour.h"

void SpidersEngine::VoxelLogic::tryFree(int x, int y, int dirX, int vX, int vY, Cluster* cluster)
{
	Voxel* freed = cluster->getVoxel(x, y);
	Voxel* next = cluster->getVoxel(x + dirX, y);
	//Chance to tag along other voxel into the fall
	if (freed && freed->data->logic && freed->behaviour == nullptr && freed->data->logic->canGoTo(next) && Random::RandPercentChance(freed->data->logic->freefallPercentChance))
	{
		freed->data->logic->free(vX, vY, freed);
	}
}
void SpidersEngine::VoxelLogic::free(int vX, int vY, Voxel* voxel)

{
	voxel->behaviour = new FreefallBehaviour(vX, -vY * voxel->data->yBounce);
	voxel->cluster->wakeVoxel(voxel->x, voxel->y);
}

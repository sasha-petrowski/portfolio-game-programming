#include "ParticleLogic.h"

#include "DefaultVoxels.h"
#include "Random.h"

namespace SpidersEngine
{


	ParticleLogic::ParticleLogic(int lifetime)
	{
		this->lifetime = lifetime;
	}

	void ParticleLogic::tick(int x, int y, Voxel* voxel, Cluster* cluster)
	{
		if (Random::RandInt() % lifetime == 0)
		{
			if (voxel->isCopy || !voxel->data->tryCool(voxel))
			{
				voxel->init(Defaults::Air);
				voxel->isCopy = false;
				voxel->cluster->setVoxel(voxel->x, voxel->y, voxel);
			}
			return;
		}

		int dirX = Random::RandInt(-1, 2);
		int dirY = Random::RandInt(-1, 2);

		Voxel* other = cluster->getVoxel(x + dirX, y + dirY);
		if (canGoTo(other))
		{
			cluster->setVoxel(x + dirX, y + dirY, voxel);
			cluster->setVoxel(x, y, other);
			return;
		}
		//else try opposite
		other = cluster->getVoxel(x - dirX, y - dirY);
		if (canGoTo(other))
		{
			cluster->setVoxel(x - dirX, y - dirY, voxel);
			cluster->setVoxel(x, y, other);
			return;
		}

		cluster->wakeVoxel(x, y);
	}

	bool ParticleLogic::canGoTo(Voxel* voxel)
	{
		return voxel && voxel->data->type == GAS;
	}
}


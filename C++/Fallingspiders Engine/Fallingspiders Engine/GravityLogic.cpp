#include "GravityLogic.h"
#include "FreefallBehaviour.h"
#include "Random.h"

namespace SpidersEngine
{

	GravityLogic::GravityLogic(int freefallPercentChance, int fallResistPercent)
	{
		this->freefallPercentChance = freefallPercentChance;
		this->gravityResistPercent = fallResistPercent;
	}

	void GravityLogic::tick(int x, int y, Voxel* voxel, Cluster* cluster)
	{
		if (canGoTo(cluster->getVoxel(x, y + 1)))
		{
			voxel->behaviour = new FreefallBehaviour(0, 1);
			voxel->behaviour->tick(x, y, voxel, cluster);
			return;
		}

		if (Random::RandPercentChance(gravityResistPercent)) return;

		int side = Random::RandSide();

		Voxel* other = cluster->getVoxel(x + side, y + 1);
		if (canGoTo(other))
		{
			cluster->setVoxel(x + side, y + 1, voxel);
			cluster->setVoxel(x, y, other);

			voxel->behaviour = new FreefallBehaviour(side / 0.75f * voxel->data->xBounce, 1);
			//voxel->behaviour->tick(x, y, voxel, chunk);
			return;
		}
		other = cluster->getVoxel(x - side, y + 1);
		if (canGoTo(other))
		{
			cluster->setVoxel(x - side, y + 1, voxel);
			cluster->setVoxel(x, y, other);

			voxel->behaviour = new FreefallBehaviour(-side / 0.75f * voxel->data->xBounce, 1);
			//voxel->behaviour->tick(x, y, voxel, chunk);
			return;
		}
		/*
		//Try to go straight down
		Voxel* other = chunk->getVoxel(x, y + 1);
		if (other && other->data->type != SOLID)
		{
			chunk->setVoxel(x, y + 1, voxel);

			if (other->data != DefaultVoxels::Air)
			{
				//select random side first
				int side = (Random::RandInt() % 2 == 0) ? 1 : -1;

				Voxel* sideVoxel = chunk->getVoxel(x + side, y);
				if (sideVoxel && sideVoxel->data != other->data && sideVoxel->data->type != SOLID)
				{
					chunk->setVoxel(x, y, sideVoxel);
					chunk->setVoxel(x + side, y, other);
					return;
				}
				sideVoxel = chunk->getVoxel(x - side, y);
				if (sideVoxel && sideVoxel->data != other->data && sideVoxel->data->type != SOLID)
				{
					chunk->setVoxel(x, y, sideVoxel);
					chunk->setVoxel(x - side, y, other);
					return;
				}
			}

			chunk->setVoxel(x, y, other);
			return;
		}

		//select random side first
		int side = (Random::RandInt() % 2 == 0) ? 1 : -1;
		other = chunk->getVoxel(x + side, y + 1);
		if (other && other->data->type != SOLID)
		{
			chunk->setVoxel(x, y, other);
			chunk->setVoxel(x + side, y + 1, voxel);
			return;
		}
		other = chunk->getVoxel(x - side, y + 1);
		if (other && other->data->type != SOLID)
		{
			chunk->setVoxel(x, y, other);
			chunk->setVoxel(x - side, y + 1, voxel);
			return;
		}
		*/
	}

	bool GravityLogic::canGoTo(Voxel* other)
	{
		return other && other->data->type != SOLID;
	}
	/*
	bool GravityLogic::canGoY(Voxel* other, int dir)
	{
		//std::cout << "CanGoY shouldn't be called inside GravityLogic\n";
		return canGoTo(other);
	}
	*/
}

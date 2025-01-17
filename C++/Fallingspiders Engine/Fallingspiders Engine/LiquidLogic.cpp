#include "LiquidLogic.h"

#include "DefaultVoxels.h"
#include "FreefallBehaviour.h"
#include "Random.h"

namespace SpidersEngine
{

	LiquidLogic::LiquidLogic(int freefallPercentChance, int fallResistPercent)
	{
		this->freefallPercentChance = freefallPercentChance;
		this->gravityResistPercent = fallResistPercent;
	}

	void LiquidLogic::tick(int x, int y, Voxel* voxel, Cluster* cluster)
	{
		Voxel* other;

		if (voxel->isCopy)
		{
			other = cluster->getVoxel(x, y - 1); // UP
			if (other && other->data->type == LIQUID) // Destroy copy if up is a liquid too
			{
				voxel->init(Defaults::Air);
				voxel->isCopy = false;
				cluster->setVoxel(x, y - 1, voxel);
				cluster->setVoxel(x, y, other);
				return;
			}
		}
		other = cluster->getVoxel(x, y + 1); // DOWN
		if (voxel->isCopy && other && (other->data->type == GAS || (Random::RandInt() % 50 == 0 && canGoTo(cluster->getVoxel(x + 1, y)) && canGoTo(cluster->getVoxel(x - 1, y))))) // Air copy if it can go down || 2% to Air it if there is nothing of the sides
		{
			voxel->init(Defaults::Air);
			voxel->isCopy = false;
			cluster->setVoxel(x, y, voxel);
			return;
		}
		//canGoY
		if (voxel->data->logic->canGoTo(other))
		{
			/*
			if (voxel->data->logic->canGoTo(cluster->getVoxel(x, y + 2)))
			{
				voxel->behaviour = new FreefallBehaviour(0, 1);
				voxel->behaviour->tick(x, y, voxel, cluster);
				return;
			}
			*/
			//cluster->setVoxel(x, y, other);
			//cluster->setVoxel(x, y + 1, voxel);
			voxel->behaviour = new FreefallBehaviour(0, 1);
			voxel->behaviour->tick(x, y, voxel, cluster);
			return;
		}

		int side = Random::RandSide();
		//canGoY
		if (voxel->data->logic->canGoTo(cluster->getVoxel(x + side, y + 1)))
		{
			//cluster->setVoxel(x, y, other);
			//cluster->setVoxel(x + side, y + 1, voxel);
			voxel->behaviour = new FreefallBehaviour(side, 1);
			voxel->behaviour->tick(x, y, voxel, cluster);
			return;
		}
		//canGoY
		if (voxel->data->logic->canGoTo(cluster->getVoxel(x - side, y + 1)))
		{
			//cluster->setVoxel(x, y, other);
			//cluster->setVoxel(x - side, y + 1, voxel);
			voxel->behaviour = new FreefallBehaviour(-side, 1);
			voxel->behaviour->tick(x, y, voxel, cluster);
			return;
		}

		other = cluster->getVoxel(x + side, y);
		if (voxel->data->logic->canGoTo(other))
		{
			if (!voxel->isCopy && Random::RandInt() % 20 == 0) //5% chance to leave a copy behing (mechanism to flood surfaces)
			{
				if (other->data == Defaults::Air) // Create copy
				{
					other->init(voxel->data);
					other->isCopy = true;
				}
			}
			cluster->setVoxel(x, y, other);
			cluster->setVoxel(x + side, y, voxel);
			voxel->behaviour = new FreefallBehaviour(side * 2, -0.2f);
			//voxel->behaviour->tick(x, y, voxel, chunk);
			return;
		}
		other = cluster->getVoxel(x - side, y);
		if (voxel->data->logic->canGoTo(other))
		{
			if (!voxel->isCopy && Random::RandInt() % 20 == 0) //5% chance to leave a copy behing (mechanism to flood surfaces)
			{
				if (other->data == Defaults::Air) // Create copy
				{
					other->init(voxel->data);
					other->isCopy = true;
				}
			}
			cluster->setVoxel(x, y, other);
			cluster->setVoxel(x - side, y, voxel);
			voxel->behaviour = new FreefallBehaviour(-side * 2, -0.2f);
			//voxel->behaviour->tick(x, y, voxel, chunk);
			return;
		}

		/*
		//Try to go straight down
		Voxel* other = chunk->getVoxel(x, y + 1);
		//std::cout << other->data->name << "\n";
		if (other && other->data->type == GAS)
		{
			chunk->setVoxel(x, y, other);
			chunk->setVoxel(x, y + 1, voxel);
			return;
		}
		//Else select random side first
		int side = (Random::RandInt() % 2 == 0) ? 1 : -1;

		Voxel* overhead = chunk->getVoxel(x + side, y - 1);
		if (!overhead || overhead->data->type != LIQUID) //If has liquid overhead, do nothing
		{
			other = chunk->getVoxel(x + side, y);
			if (other && other->data->type == GAS)
			{
				chunk->setVoxel(x, y, other);
				chunk->setVoxel(x + side, y, voxel);
				return;
			}
		}

		overhead = chunk->getVoxel(x - side, y - 1);
		if (!overhead || overhead->data->type != LIQUID) //If has liquid overhead, do nothing
		{
			other = chunk->getVoxel(x - side, y);
			if (other && other->data->type == GAS)
			{
				chunk->setVoxel(x, y, other);
				chunk->setVoxel(x - side, y, voxel);
				return;
			}
		}
		*/
	}

	bool LiquidLogic::canGoTo(Voxel* other)
	{
		return other && (other->data->type == GAS || (other->data->type == LIQUID && other->data->weight < data->weight));
	}
	/*
	bool LiquidLogic::canGoY(Voxel* other, int dir)
	{
		return other && other->data->weight * dir < data->weight * dir;
	}
	*/
}

#include <iostream>

#include "FreefallBehaviour.h"
#include "Random.h"


namespace SpidersEngine
{

	FreefallBehaviour::FreefallBehaviour(int vX, int vY)
	{
		this->vX = vX;
		this->vY = vY;
	}

	void FreefallBehaviour::tick(int x, int y, Voxel* voxel, Cluster* cluster)
	{
		//pseudo Air resistance decceleration
		vX = vX * 0.975f;
		//pseudo Gravity acceleration
		vY += 0.1f;

		if (vY > -1 && vY < 1)
		{
			vY += 0.5f;
			cluster->wakeVoxel(x, y);
		}

		bool frictionApplied = false;

		int traversalX = floor(vX) + (vX - floor(vX) > Random::RandF(1) ? 1 : 0);
		int traversalY = floor(vY) + (vY - floor(vY) > Random::RandF(1) ? 1 : 0);

		int startX = x;
		int startY = y;

		int traversedX = 0;
		int traversedY = 0;

		float steps = floorf(sqrt(traversalX * traversalX + traversalY * traversalY));

		float t;
		int otherX;
		int otherY;
		Voxel* other;

		int dirX = (traversalX > 0) ? 1 : (traversalX < 0) ? -1 : 0;
		int dirY = (traversalY > 0) ? 1 : (traversalY < 0) ? -1 : 0;

		for (int i = 1; i <= steps; i++)
		{
			t = i / steps;
			otherX = startX + t * (traversalX);
			otherY = startY + t * (traversalY);

			if (otherX == x && otherY == y) continue;

			other = cluster->getVoxel(otherX, otherY);

			if (dirX != 0)
			{
				voxel->data->logic->tryFree(x + dirX, y + dirY, dirX, vX, vY, cluster);
				if (dirY != 0)
				{
					voxel->data->logic->tryFree(x, y + dirY, dirX, vX, vY, cluster);
					voxel->data->logic->tryFree(x - dirX, y + dirY, dirX, vX, vY, cluster);
				}
			}

			if (voxel->data->logic->canGoTo(other))
			{
				cluster->setVoxel(otherX, otherY, voxel);
				cluster->setVoxel(x, y, other);

				x = otherX;
				y = otherY;
			}
			else
			{
				cluster->wakeVoxel(x, y);

				if ((other && other->behaviour && typeid(*other->behaviour) == typeid(*voxel->behaviour))) continue;

				if (otherY - y != 0)
				{
					//surface friction decceleration
					if (!frictionApplied)
					{
						frictionApplied = true;
						vX -= vX * voxel->data->surfaceFriction;
					}

					float bounceVariance = Random::RandF(1 - voxel->data->bounceVariance, 1.0f);
					if (vY > 1.5f || vY < -1.5f) //Transfer Y velocity to X
					{
						if (vX < -.1f) { vX -= vY * bounceVariance * voxel->data->xBounce; }
						else if (vX > .1f) { vX += vY * bounceVariance * voxel->data->xBounce; }
						else { vX += vY * Random::RandSide() * bounceVariance * voxel->data->xBounce; }
					}

					// reduce Y Velocity
					vY = vY * -voxel->data->yBounce * bounceVariance;

					dirX = (vX > .1f) ? 1 : (vX < -.1f) ? -1 : 0;
					if (dirX != 0)
					{
						voxel->data->logic->tryFree(x + dirX * 2, y + dirY, dirX, vX, vY, cluster);
						if (dirY != 0)
						{
							voxel->data->logic->tryFree(x + dirX, y + dirY * 2, dirX, vX, vY, cluster);
						}
					}
				}
				else if (otherX - x != 0)
				{
					vX = 0;
				}

				if ((vY > -1 && vY <= 1) && (vX > -1 && vX <= 1))
				{
					voxel->behaviour = nullptr;
					delete this;
					return;
				}

				break;
			}
		}
	}

}

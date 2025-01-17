#include "LerpColorTemplate.h"
#include "DefaultVoxels.h"
#include "Random.h"

#include "Mathf.h"


namespace SpidersEngine
{
	namespace ColorGeneration
	{
		LerpColorTemplate::LerpColorTemplate(uint32_t rA, uint32_t gA, uint32_t bA, uint32_t aA, uint32_t rB, uint32_t gB, uint32_t bB, uint32_t aB)
		{
			this->rA = rA;
			this->gA = gA;
			this->bA = bA;
			this->aA = aA;

			this->rB = rB;
			this->gB = gB;
			this->bB = bB;
			this->aB = aB;
		}

		uint32_t LerpColorTemplate::GetColor(int x, int y)
		{
			const float t = Random::RandF(1);
			const float tM = 1 - t;

			return SDL_MapRGBA(
				Defaults::PixelFormat,
				(t * rA) + (tM * rB),
				(t * gA) + (tM * gB),
				(t * bA) + (tM * bB),
				(t * aA) + (tM * aB));
		}



	}
}
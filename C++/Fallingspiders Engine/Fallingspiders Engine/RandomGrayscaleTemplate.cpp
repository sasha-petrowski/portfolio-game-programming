#include "RandomGrayscaleTemplate.h"

#include "SDL.h"
#include "Random.h"
#include "DefaultVoxels.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		RandomGrayscaleTemplate::RandomGrayscaleTemplate(float variance, uint32_t r, uint32_t g, uint32_t b, uint32_t a)
		{
			this->variance = variance;

			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		uint32_t RandomGrayscaleTemplate::GetColor(int x, int y)
		{
			float t = 1 - Random::RandF(variance);
			return SDL_MapRGBA(
				Defaults::PixelFormat,
				t * r,
				t * g,
				t * b,
				a);
		}
	}
}
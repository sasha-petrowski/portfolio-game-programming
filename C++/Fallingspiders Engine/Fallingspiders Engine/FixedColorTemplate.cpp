#include "FixedColorTemplate.h"

#include "SDL.h"
#include "Random.h"
#include "DefaultVoxels.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		FixedColorTemplate::FixedColorTemplate(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
		{
			this->color = SDL_MapRGBA(
				Defaults::PixelFormat,
				r,
				g,
				b,
				a);
		}

		uint32_t FixedColorTemplate::GetColor(int x, int y)
		{
			return color;
		}
	}
}
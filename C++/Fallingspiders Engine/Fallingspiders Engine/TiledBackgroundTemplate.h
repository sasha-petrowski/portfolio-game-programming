#pragma once

#include "ColorTemplate.h"
#include "SDL.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class TiledBackgroundTemplate : public ColorTemplate
		{
		public:
			int pixelScale;
			uint32_t colorA;
			uint32_t colorB;

			TiledBackgroundTemplate();
			TiledBackgroundTemplate(int pixelScale, uint32_t colorA, uint32_t colorB);

			uint32_t GetColor(int x, int y);
		};
	}
}


#include "TiledBackgroundTemplate.h"
#include "DefaultVoxels.h"



SpidersEngine::ColorGeneration::TiledBackgroundTemplate::TiledBackgroundTemplate() : TiledBackgroundTemplate(16, SDL_MapRGBA(Defaults::PixelFormat, 75, 75, 75, 80), SDL_MapRGBA(Defaults::PixelFormat, 90, 90, 90, 90))
{
}

SpidersEngine::ColorGeneration::TiledBackgroundTemplate::TiledBackgroundTemplate(int pixelScale, uint32_t colorA, uint32_t colorB)
{
	this->pixelScale = pixelScale;
	this->colorA = colorA;
	this->colorB = colorB;
}


uint32_t SpidersEngine::ColorGeneration::TiledBackgroundTemplate::GetColor(int x, int y)
{
	int index = x / pixelScale + y / pixelScale;

	x = x % pixelScale;
	y = y % pixelScale;
	const int max = pixelScale - 1;

	if (index % 2 == 0)
	{
		if (x == 0 || y == 0 || x == max || y == max)
		{
			return colorB;
		}
		return colorA;
	}
	else
	{
		if (x == 0 || y == 0 || x == max || y == max)
		{
			return colorA;
		}
		return colorB;
	}
}

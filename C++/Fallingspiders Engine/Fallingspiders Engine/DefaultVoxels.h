#pragma once
#include "VoxelData.h"
#include "SDL.h"


namespace SpidersEngine
{

	class VoxelData;

	namespace Defaults
	{
		//True Solids
		extern VoxelData* Metal;
		extern VoxelData* Wood;
		extern VoxelData* Coal;

		//Gravity affected Solids
		extern VoxelData* Sand;
		extern VoxelData* Dirt;
		extern VoxelData* Gravel;

		//Gases
		extern VoxelData* Air;
		extern VoxelData* Steam;
		extern VoxelData* Smoke;
		extern VoxelData* Fire;
		extern VoxelData* Hydrogen;

		//Liquids
		extern VoxelData* Water;
		extern VoxelData* Oil;

		//Other
		extern SDL_PixelFormat* PixelFormat;
	}
}

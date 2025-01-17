#include "Game.h"

#include "DefaultVoxels.h"
#include "GravityLogic.h"
#include "LiquidLogic.h"
#include "GasLogic.h"
#include "VaporLogic.h"
#include "ParticleLogic.h"

#include "HeatReaction.h"
#include "BurnReaction.h"
#include "BurnChanceReaction.h"

#include "ColorTemplate.h"
#include "RandomGrayscaleTemplate.h"
#include "FixedColorTemplate.h"
#include "NoisyHexagonTemplate.h"
#include "LerpColorTemplate.h"


namespace SpidersEngine
{
	namespace Defaults
	{
		//True Solids
		VoxelData* Metal;
		VoxelData* Wood;
		VoxelData* Coal;

		//Gravity affected Solids
		VoxelData* Sand;
		VoxelData* Dirt;
		VoxelData* Gravel;

		//Gases
		VoxelData* Air;
		VoxelData* Steam;
		VoxelData* Smoke;
		VoxelData* Fire;
		VoxelData* Hydrogen;

		//Liquids
		VoxelData* Water;
		VoxelData* Oil;

		//Other
		SDL_PixelFormat* PixelFormat;
	}

	using namespace Defaults;
	using namespace ColorGeneration;

	void Game::initDefaults()
	{
		Defaults::PixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

		//True Solids
#pragma region METAL
		Metal = new VoxelData(
			"Metal",
			8000,
			SOLID,
			new NoisyHexagonTemplate(8, 155, 155, 155, 255),
			nullptr
		);
#pragma endregion
#pragma region WOOD
		Wood = new VoxelData(
			"Wood",
			900,
			SOLID,
			new NoisyHexagonTemplate(5, 114, 73, 30, 255),
			nullptr
		);
		Wood->hotterData = &Coal;
		Wood->reactions = new std::vector<VoxelReaction*>{ new BurnChanceReaction(25) };
#pragma endregion
#pragma region COAL
		Coal = new VoxelData(
			"Coal",
			2000,
			SOLID,
			new RandomGrayscaleTemplate(0.2f, 32, 16, 16, 255),
			nullptr
		);
		Coal->hotterData = &Fire;
		Coal->reactions = new std::vector<VoxelReaction*>{ new BurnChanceReaction(50) };
#pragma endregion

		//Gravity affected Solids
#pragma region SAND
		Sand = new VoxelData(
			"Sand",
			1800,
			SOLID,
			new RandomGrayscaleTemplate(0.2f, 255, 200, 0, 255),
			new GravityLogic(100, 0)
		);
#pragma endregion
#pragma region DIRT
		Dirt = new VoxelData(
			"Dirt",
			1600,
			SOLID,
			new RandomGrayscaleTemplate(0.2f, 111, 78, 55, 255),
			new GravityLogic(15, 75)
		);
		Dirt->surfaceFriction = 0.75f;
		Dirt->xBounce = 0.4f;
#pragma endregion
#pragma region GRAVEL
		Gravel = new VoxelData(
			"Gravel",
			2000,
			SOLID,
			new RandomGrayscaleTemplate(0.2f, 100, 100, 100, 255),
			new GravityLogic(30, 50)
		);
		Gravel->xBounce = 0.5f;
#pragma endregion

		//Gases
#pragma region AIR
		Air = new VoxelData(
			"Air",
			0,
			GAS,
			new FixedColorTemplate(0, 0, 0, 0),
			nullptr
		);
#pragma endregion
#pragma region STEAM
		Steam = new VoxelData(
			"Steam",
			-100,
			GAS,
			new RandomGrayscaleTemplate(0.1f, 255, 255, 255, 64),
			new VaporLogic(66, 10, 1000)
		);
		Steam->colderData = &Water;
#pragma endregion
#pragma region SMOKE
		Smoke = new VoxelData(
			"Smoke",
			-50,
			GAS,
			new RandomGrayscaleTemplate(0.2f, 32, 32, 32, 128),
			new VaporLogic(66, 20, 1000)
		);
#pragma endregion
#pragma region HYDROGEN
		Hydrogen = new VoxelData(
			"Hydrogen",
			-40,
			GAS,
			new RandomGrayscaleTemplate(.2f, 255, 0, 255, 32),
			new GasLogic(50)
		);
		Hydrogen->hotterData = &Fire;
		Hydrogen->reactions = new std::vector<VoxelReaction*>{ new BurnReaction() };
#pragma endregion
#pragma region FIRE
		Fire = new VoxelData(
			"Fire",
			-40,
			GAS,
			new LerpColorTemplate(255, 0, 0, 255, 255, 128, 32, 255),
			new ParticleLogic(250)
		);
		Fire->colderData = &Smoke;
		Fire->isHot = true;
#pragma endregion

		//Liquids
#pragma region WATER
		Water = new VoxelData(
			"Water",
			1000,
			LIQUID,
			new RandomGrayscaleTemplate(0.1f, 0, 0, 255, 155),
			new LiquidLogic(100)
		);
		Water->surfaceFriction = 0.25f;
		Water->yBounce = 0.33f;
		Water->xBounce = 0.25f;
		Water->hotterData = &Steam;
		Water->reactions = new std::vector<VoxelReaction*>{ new HeatReaction() };
#pragma endregion
#pragma region OIL
		Oil = new VoxelData(
			"Oil",
			880,
			LIQUID,
			new RandomGrayscaleTemplate(0.1f, 48, 32, 32, 155),
			new LiquidLogic(100)
		);
		Oil->surfaceFriction = 0.25f;
		Oil->yBounce = 0.5f;
		Oil->xBounce = 0.33f;
		Oil->hotterData = &Fire;
		Oil->reactions = new std::vector<VoxelReaction*>{ new BurnReaction() };
#pragma endregion
	}
}

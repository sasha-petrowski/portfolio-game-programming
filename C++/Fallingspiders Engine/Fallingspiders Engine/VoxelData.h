#pragma once
#include <string>
#include <vector>

#include "SDL.h"

#include "ColorTemplate.h"
#include "VoxelLogic.h"
#include "VoxelReaction.h"

namespace SpidersEngine
{
	using namespace ColorGeneration;

	class VoxelLogic;
	class VoxelReaction;

	enum VoxelType
	{
		SOLID,
		LIQUID,
		GAS,
	};

	class VoxelData
	{
	public:
		std::string name;
		int weight;
		VoxelType type;
		ColorTemplate* colorTemplate;
		VoxelLogic* logic;
		std::vector<VoxelReaction*>* reactions;



		bool isHot = false;
		bool isCold = false;

		float surfaceFriction = 0.5f;
		float xBounce = 0.75f;
		float yBounce = -0.25f;
		float bounceVariance = 0.5f;

		VoxelData** hotterData;
		VoxelData** colderData;

		VoxelData(std::string name, int weight, VoxelType type, ColorTemplate* colorTemplate, VoxelLogic* logic);
		~VoxelData();

		bool tryHeat(Voxel* voxel);
		bool tryCool(Voxel* voxel);
	};

	std::ostream& operator<<(std::ostream& stream, const VoxelData* data);

}

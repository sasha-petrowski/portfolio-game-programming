#include "VoxelData.h"
#include "DefaultVoxels.h"

namespace SpidersEngine
{

	VoxelData::VoxelData(std::string name, int weight, VoxelType type, ColorTemplate* colorTemplate, VoxelLogic* logic)
	{
		this->name = name;
		this->weight = weight;
		this->type = type;
		this->colorTemplate = colorTemplate;
		this->logic = logic;

		if (logic)
		{
			if (logic->data) throw("Logic already had a voxelData attributed to it.");
			logic->data = this;
		}
	}

	VoxelData::~VoxelData()
	{
		for (auto ptr : *reactions)
		{
			delete ptr;
		}
		reactions->clear();
		delete reactions;
	}
	
	bool VoxelData::tryHeat(Voxel* voxel)
	{
		if (hotterData)
		{
			//cleanup any behaviour
			if (voxel->behaviour)
			{
				delete voxel->behaviour;
				voxel->behaviour = nullptr;
			}

			if (voxel->isCopy)
			{
				voxel->isCopy = false;
				voxel->init(Defaults::Air);
			}
			else voxel->init(*hotterData);

			voxel->cluster->setVoxel(voxel->x, voxel->y, voxel);
			return true;
		}
		return false;
	}

	bool VoxelData::tryCool(Voxel* voxel)
	{
		if (colderData)
		{
			//cleanup any behaviour
			if (voxel->behaviour)
			{
				delete voxel->behaviour;
				voxel->behaviour = nullptr;
			}

			if (voxel->isCopy)
			{
				voxel->isCopy = false;
				voxel->init(Defaults::Air);
			}
			else voxel->init(*colderData);

			voxel->cluster->setVoxel(voxel->x, voxel->y, voxel);
			return true;
		}
		return false;
	}

	std::ostream& operator<<(std::ostream& stream, const VoxelData* data)
	{
		stream << data->name << " T.";

		switch (data->type)
		{
		case SOLID:
			stream << "SOLID";
			break;
		case LIQUID:
			stream << "LIQUID";
			break;
		case GAS:
			stream << "GAS";
			break;
		}

		return stream;
	}
}

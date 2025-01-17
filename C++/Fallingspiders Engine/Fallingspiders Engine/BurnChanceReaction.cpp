#include "BurnChanceReaction.h"
#include "Random.h"
#include "DefaultVoxels.h"

SpidersEngine::BurnChanceReaction::BurnChanceReaction(int burnChance)
{
    this->burnChance = burnChance;
}

bool SpidersEngine::BurnChanceReaction::tryReact(Voxel* self, Voxel* other)
{
    if (other->data->isHot && Random::RandPercentChance(burnChance))
    {
        react(self, other);
        return true;
    }
    return false;
}

void SpidersEngine::BurnChanceReaction::react(Voxel* self, Voxel* other)
{
    self->data->tryHeat(self);
}

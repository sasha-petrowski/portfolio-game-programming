#include "BurnReaction.h"
#include "DefaultVoxels.h"

bool SpidersEngine::BurnReaction::tryReact(Voxel* self, Voxel* other)
{
    if (other->data->isHot)
    {
        react(self, other);
        return true;
    }
    return false;
}

void SpidersEngine::BurnReaction::react(Voxel* self, Voxel* other)
{
    self->data->tryHeat(self);
}

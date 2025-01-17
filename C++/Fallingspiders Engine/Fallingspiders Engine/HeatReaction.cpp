#include "HeatReaction.h"

bool SpidersEngine::HeatReaction::tryReact(Voxel* self, Voxel* other)
{
    if (other->data->isHot)
    {
        react(self, other);
        return true;
    }
    return false;
}

void SpidersEngine::HeatReaction::react(Voxel* self, Voxel* other)
{
    if (!self->isCopy) other->data->tryCool(other);
    self->data->tryHeat(self);
}

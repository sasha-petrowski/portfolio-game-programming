#include "Random.h"
#include <cstdlib>
namespace SpidersEngine
{

    int Random::RandSide()
    {
        return 1 - (std::rand() % 2) * 2;
    }

    int Random::RandInt()
    {
        return std::rand();
    }

    int Random::RandInt(int max)
    {
        return std::rand() / ((RAND_MAX + 1u) / max);
    }

    int Random::RandInt(int min, int max)
    {
        return min + std::rand() / ((RAND_MAX + 1u) / (max - min));
    }

    float Random::RandF(float max)
    {
        return std::rand() / ((RAND_MAX + 1u) / max);
    }

    float Random::RandF(float min, float max)
    {
        return (float)(min + std::rand() / ((RAND_MAX + 1u) / (max - min)));
    }

    bool Random::RandPercentChance(int percent)
    {
        return percent == 100 ? true : percent == 0 ? false : percent > std::rand() / ((RAND_MAX + 1u) / 100);;
    }
}

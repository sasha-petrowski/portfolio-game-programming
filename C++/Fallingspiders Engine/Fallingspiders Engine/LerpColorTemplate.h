#pragma once
#include "ColorTemplate.h"
#include "SimplexNoise.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class LerpColorTemplate : public ColorTemplate
		{
		public:
			uint8_t rA, gA, bA, aA;
			uint8_t rB, gB, bB, aB;

			LerpColorTemplate(uint32_t rA, uint32_t gA, uint32_t bA, uint32_t aA, uint32_t rB, uint32_t gB, uint32_t bB, uint32_t aB);

			uint32_t GetColor(int x, int y);
		};
	}
}


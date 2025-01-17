#pragma once
#include "ColorTemplate.h"
#include "SimplexNoise.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class NoisyHexagonTemplate : public ColorTemplate
		{
		public:
			uint8_t r, g, b, a;

			NoisyHexagonTemplate() : NoisyHexagonTemplate(8, 75, 75, 75, 255) {};
			NoisyHexagonTemplate(int pixelScale, uint32_t r, uint32_t g, uint32_t b, uint32_t a);

			uint32_t GetColor(int x, int y);

		private:
			float mScale;
			Noise::SimplexNoise* mNoiseDarken;
			Noise::SimplexNoise* mNoiseX;
			Noise::SimplexNoise* mNoiseY;
		};
	}
}


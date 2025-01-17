#include "NoisyHexagonTemplate.h"
#include "DefaultVoxels.h"
#include "Random.h"

#include "Mathf.h"


namespace SpidersEngine
{
	namespace ColorGeneration
	{
		// hexagonal distance
		NoisyHexagonTemplate::NoisyHexagonTemplate(int pixelScale, uint32_t r, uint32_t g, uint32_t b, uint32_t a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;

			mScale = 1.0f / pixelScale;

			mNoiseDarken = new Noise::SimplexNoise(mScale * 2, 0.15f);
			mNoiseX = new Noise::SimplexNoise(mScale, mScale * 2);
			mNoiseY = new Noise::SimplexNoise(mScale, mScale * 2);
		}

		uint32_t NoisyHexagonTemplate::GetColor(int x, int y)
		{
			Vector2 size = *new Vector2(1, 1.7320508f);
			Vector2 pos = *new Vector2(x * mScale + mNoiseX->noise2D(x, y), y * mScale + mNoiseY->noise2D(x, y));

			Vector2 hexCenterA = *new Vector2(floorf(pos.x / size.x) + 0.5f, floorf(pos.y / size.y) + 0.5f);
			Vector2 hexCenterB = *new Vector2(floorf((pos.x - 0.5f) / size.x) + 0.5f, floorf((pos.y - 1) / size.y) + 0.5f);

			Vector2 offsetA = *new Vector2(pos.x - hexCenterA.x * size.x, pos.y - hexCenterA.y * size.y);
			Vector2 offsetB = *new Vector2(pos.x - (hexCenterB.x + .5f) * size.x, pos.y - (hexCenterB.y + .5f) * size.y);

			Vector2 hexCenter = *new Vector2(0, 0);
			Vector2 hexOffset = *new Vector2(0, 0);

			bool randomDarker = false;
			if (Mathf::dot(offsetA, offsetA) < Mathf::dot(offsetB, offsetB))
			{
				//hexCenter = hexCenterA;
				hexOffset = offsetA;
			}
			else
			{
				//hexCenter = hexCenterB;
				hexOffset = offsetB;
			}

			hexOffset.x = fabsf(hexOffset.x);
			hexOffset.y = fabsf(hexOffset.y);

			// Represents the lerp from the hex's center : 1 near the edges, 0 near the center
			float hexDistance = fmaxf(Mathf::dot(hexOffset, size * 0.5f), hexOffset.x) * 2;

			float t = 1 - hexDistance * 0.25f - mNoiseDarken->noise2D(x, y) * (1 - hexDistance);
			
			if (t > 1) t = 1;

			return SDL_MapRGBA(
				Defaults::PixelFormat,
				t * r,
				t * g,
				t * b,
				a);
		}

		
	}
}
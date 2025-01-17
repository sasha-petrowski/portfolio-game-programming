#pragma once
#include "ColorTemplate.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class RandomGrayscaleTemplate : public ColorTemplate
		{
		public:
			float variance = 0;
			uint8_t r, g, b, a;

			RandomGrayscaleTemplate(float variance, uint32_t r, uint32_t g, uint32_t b, uint32_t a);

			uint32_t GetColor(int x, int y);
		};
	}
}
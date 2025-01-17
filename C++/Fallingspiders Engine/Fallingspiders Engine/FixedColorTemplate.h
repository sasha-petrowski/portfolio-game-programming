#pragma once
#include "ColorTemplate.h"

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class FixedColorTemplate : public ColorTemplate
		{
		public:
			uint32_t color;

			FixedColorTemplate(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

			uint32_t GetColor(int x, int y);
		};
	}
}
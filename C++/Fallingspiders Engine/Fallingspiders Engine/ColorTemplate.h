#pragma once
#include <iostream>

namespace SpidersEngine
{
	namespace ColorGeneration
	{
		class ColorTemplate
		{
		public:
			virtual uint32_t GetColor(int x, int y) = 0;
		};
	}
}
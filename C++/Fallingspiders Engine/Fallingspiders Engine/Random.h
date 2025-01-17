#pragma once

namespace SpidersEngine
{
	static class Random
	{
	public:
		static int RandSide();

		static int RandInt();
		static int RandInt(int max);
		static int RandInt(int min, int max);

		static float RandF(float max);
		static float RandF(float min, float max);

		static bool RandPercentChance(int percent);
	};
}

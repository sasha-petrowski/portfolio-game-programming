/**
 * @file    SimplexNoise.h
 * @brief   A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D).
 *
 * Copyright (c) 2014-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */
#pragma once

#include <cstddef>  // size_t
#include <iostream>

 /**
  * @brief A Perlin Simplex Noise C++ Implementation (1D, 2D, 3D, 4D).
  */
namespace SpidersEngine
{
	namespace Noise
	{
        class SimplexNoise {
        public:
            // 1D Perlin simplex noise
            float noise1D(float x);
            // 2D Perlin simplex noise
            float noise2D(float x, float y);
            // 3D Perlin simplex noise
            float noise3D(float x, float y, float z);

            /**
             * Constructor of to initialize a fractal noise summation
             *
             * @param[in] frequency    Frequency ("width") of the first octave of noise (default to 1.0)
             * @param[in] amplitude    Amplitude ("height") of the first octave of noise (default to 1.0)
             */
            explicit SimplexNoise(float frequency = 1.0f, float amplitude = 1.0f)
            {
                mFrequency = frequency;
                mAmplitude = amplitude;

                xx = std::rand();
                yy = std::rand();
                zz = std::rand();
            }

        private:
            float mFrequency;   ///< Frequency ("width") of the noise (default to 1.0)
            float mAmplitude;   ///< Amplitude ("height") of the noise (default to 1.0)

            float xx, yy, zz;   ///< Random Offset to the noise
        };
	}
}


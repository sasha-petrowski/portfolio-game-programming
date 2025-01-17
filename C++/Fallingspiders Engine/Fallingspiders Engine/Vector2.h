#pragma once


namespace SpidersEngine
{
	struct Vector2
	{
	public:
		float x, y;

		Vector2(float x, float y);

		Vector2 operator*(float const& obj);

		Vector2 operator*(Vector2 const& obj);

		Vector2 operator+(float const& obj);

		Vector2 operator+(Vector2 const& obj);

		Vector2 operator-(float const& obj);

		Vector2 operator-(Vector2 const& obj);
	};
}


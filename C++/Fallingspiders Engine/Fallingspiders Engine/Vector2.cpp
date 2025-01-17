#include "Vector2.h"

namespace SpidersEngine
{
	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 Vector2::operator*(float const& obj)
	{
		return *new Vector2(x * obj, y * obj);
	}

	Vector2 Vector2::operator*(Vector2 const& obj)
	{
		return *new Vector2(x * obj.x, y * obj.y);
	}

	Vector2 Vector2::operator+(float const& obj)
	{
		return *new Vector2(x + obj, y + obj);
	}

	Vector2 Vector2::operator+(Vector2 const& obj)
	{
		return *new Vector2(x + obj.x, y + obj.y);
	}

	Vector2 Vector2::operator-(float const& obj)
	{
		return *new Vector2(x - obj, y - obj);
	}

	Vector2 Vector2::operator-(Vector2 const& obj)
	{
		return *new Vector2(x - obj.x, y - obj.y);
	}
}

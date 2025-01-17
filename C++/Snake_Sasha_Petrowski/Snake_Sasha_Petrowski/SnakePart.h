#pragma once
#include "Snake.h"

typedef enum { Head, Tail, Body } BodyType;
typedef enum { Left, Right, Top, Bottom } Direction;

const std::vector<Direction> LeftDirections(
	{
	Direction::Left,
	Direction::Top,
	Direction::Bottom
	}
);
const std::vector<Direction> RightDirections(
	{
	Direction::Right,
	Direction::Top,
	Direction::Bottom
	}
);
const std::vector<Direction> TopDirections(
	{
	Direction::Left,
	Direction::Right,
	Direction::Top
	}
);
const std::vector<Direction> BottomDirections(
	{
	Direction::Left,
	Direction::Right,
	Direction::Bottom
	}
);
const std::vector<sf::Vector2i> DirectionVector(
	{
	sf::Vector2i(1,0),
	sf::Vector2i(-1,0),
	sf::Vector2i(0,1),
	sf::Vector2i(0,-1)
	}
);
class SnakePart {
public : 
	static Direction InveverseOf(Direction _direction) {
		switch (_direction)
		{
		case Direction::Left:
			return Direction::Right;

		case Direction::Right:
			return Direction::Left;

		case Direction::Top:
			return Direction::Bottom;

		case Direction::Bottom:
			return Direction::Top;

		default:
			break;
		}
	}

	static sf::Vector2i DirectionToVector(Direction _direction) {
		switch (_direction)
		{
		case Direction::Left:
			return DirectionVector[0];

		case Direction::Right:
			return DirectionVector[1];

		case Direction::Top:
			return DirectionVector[2];

		case Direction::Bottom:
			return DirectionVector[3];

		default:
			break;
		}
	}
	static std::vector<Direction> DirectionToPossibleDirections(Direction _direction) {
		switch (_direction)
		{
		case Direction::Left:
			return LeftDirections;

		case Direction::Right:
			return RightDirections;

		case Direction::Top:
			return TopDirections;

		case Direction::Bottom:
			return BottomDirections;

		default:
			break;
		}
	}

	SnakePart() {

	}
	SnakePart(const sf::Vector2i _position, SnakePart* _next, SnakePart* _previous, BodyType _body_type, Direction _direction) {
		distance = 0;
		position = _position;
		next = _next;
		previous = _previous;
		body_type = _body_type;
		direction = _direction;
	}

	int ToTile() {
		if (body_type == BodyType::Head) {
			switch (direction)
			{
			case Direction::Top:
				return 3;

			case Direction::Bottom:
				return 9;

			case Direction::Right:
				return 4;

			case Direction::Left:
				return 8;

			default:
				break;
			}
		}
		else if (body_type == BodyType::Tail) {
			switch (direction)
			{
			case Direction::Top:
				return 13;

			case Direction::Bottom:
				return 19;

			case Direction::Right:
				return 14;

			case Direction::Left:
				return 18;

			default:
				break;
			}
		}
		else {
			switch (direction)
			{
			case Direction::Top:
				if (previous->direction == Direction::Right)
				{
					return 12;
				}else if (previous->direction == Direction::Left) {
					return 5;				
				}else
					return 7;

			case Direction::Bottom:
				if (previous->direction == Direction::Right)
				{
					return 2;
				}
				else if (previous->direction == Direction::Left) {
					return 0;
				}else
					return 7;

			case Direction::Right:
				if (previous->direction == Direction::Bottom)
				{
					return 5;
				}
				else if (previous->direction == Direction::Top) {
					return 0;
				}else
					return 1;

			case Direction::Left:
				if (previous->direction == Direction::Bottom)
				{
					return 12;
				}
				else if (previous->direction == Direction::Top) {
					return 2;
				}else
					return 1;

			default:
				break;
			}
		}
		return 6;
	}

	SnakePart* GetTail() {
		if (body_type == BodyType::Tail) {
			return this;
		}
		else {
			return previous->GetTail();
		}
	}
	 
	SnakePart* AddTail() {
		distance += 1;

		if (body_type == BodyType::Tail) {
			body_type = BodyType::Body;
			previous = new SnakePart(sf::Vector2i(position.x + DirectionToVector(direction).x, position.y + DirectionToVector(direction).y), this, NULL, BodyType::Tail, direction);
			return previous;
		}
		else if(body_type == BodyType::Head && previous == NULL) {
			previous = new SnakePart(sf::Vector2i(position.x + DirectionToVector(direction).x, position.y + DirectionToVector(direction).y), this, NULL, BodyType::Tail, direction);
			return previous;
		}else {
			return previous->AddTail();
		}
	}

	void Move() {
		position = position - DirectionToVector(direction);
		if(next != NULL)
			direction = next->direction;
	}


	int distance;
	sf::Vector2i position;
	SnakePart* next;
	SnakePart* previous;
	BodyType body_type;
	Direction direction;
};
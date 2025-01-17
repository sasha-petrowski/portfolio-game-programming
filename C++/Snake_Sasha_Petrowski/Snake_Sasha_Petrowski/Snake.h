#pragma once
#include <stdio.h>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "SnakePart.h"
#include "PathfindingAlgorithm.h"


class Snake {
public:
	/*retourne true si la position est dans les limites de la dimension, false sinon.*/
	static bool inbounds(const std::vector<std::vector<SnakePart*>>& _grid, const sf::Vector2i& position) {
		return (position.x > 0 && position.y > 0 && position.x < _grid.size() - 1 && position.y < _grid[position.x].size() - 1);
	}

	/*retourne true si le snake peut aller sur la case en paramètre, false sinon.*/
	static bool can_move_to(const std::vector<std::vector<SnakePart*>>& _grid, const sf::Vector2i& position, int distance) {
		/* DEBUG
		if (inbounds(_grid, position)) {
			if (_grid[position.x][position.y] == NULL) {
				std::cout << "Tile vide" << std::endl;
			}
			else {
				std::cout << "Tile snake : Distance : " << (_grid[position.x][position.y]->distance - distance) << std::endl;
			}
		}
		else {
			std::cout << "OUTBOUNDS : " << position.x << "/" << position.y << std::endl;
		}
		*/
		return (inbounds(_grid, position) && ((_grid[position.x][position.y] == NULL) || (_grid[position.x][position.y]->distance - distance) < 0));
	}

	Snake() {

	}
	Snake(int _startsize, sf::Vector2i _dimension, bool automatic) {
		m_dimension = _dimension;

		m_grid.resize(this->m_dimension.x);
		for (int i = 0; i < this->m_dimension.x; i++) {
			m_grid[i].resize(this->m_dimension.y);
		}
		m_next_direction = Direction::Right;
		m_head = new SnakePart(sf::Vector2i(_dimension.x/2, _dimension.y/2), NULL, NULL, BodyType::Head, Direction::Right);
		m_grid[m_head->position.x][m_head->position.y] = m_head;
		for (int i = 0; i < _startsize - 1; i++) {
			m_tail = m_head->AddTail();
			if (inbounds(m_grid, m_tail->position)) {
				m_grid[m_tail->position.x][m_tail->position.y] = m_tail;
			}
		}
		NewApplePosition();

		if (automatic) {
			m_pathfinding = PathfindingAlgorithm(m_grid);
			UpdatePathfinding();
		}
	}

	bool Move() {
		/*déplace le snake en fonction de sa direction lorsque c’est possible. Sinon, fin de la partie.*/
		m_head->direction = m_next_direction;
		if (can_move_to(m_grid, m_head->position - SnakePart::DirectionToVector(m_head->direction), 1)) {
			bool apple = false;
			if (m_head->position - SnakePart::DirectionToVector(m_head->direction) == m_apple_position) {
				m_tail = m_head->AddTail();
				apple = true;
			}
			SnakePart* part = m_tail;
			m_grid[m_tail->position.x][m_tail->position.y] = NULL;
			while (part != NULL) {
				part->Move();
				m_grid[part->position.x][part->position.y] = part;
				part = part->next;
			}
			if (apple) {
				NewApplePosition();
			}
			return true;
		}
		else {
			return false;
		}
	}

	void setDirection(Direction _direction) {
		if (_direction != SnakePart::InveverseOf(m_head->direction)) {
			m_next_direction = _direction;
		}
	}

	std::vector<std::vector<int>> GridToTiles() {
		std::vector<std::vector<int>> tiles;
		tiles.resize(m_dimension.x);
		for (int x = 0; x < m_dimension.x; x++) {
			tiles[x].resize(m_dimension.y);
			for (int y = 0; y < m_dimension.y; y++) {
				if (m_apple_position.x == x && m_apple_position.y == y) {
					tiles[x][y] = 15;
				}
				else if (m_grid[x][y] == NULL) {
					tiles[x][y] = 6;
				}
				else{
					tiles[x][y] = m_grid[x][y]->ToTile();
				}
			}
		}
		return tiles;
	}

	void keyboard_event()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			setDirection(Direction::Top);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			setDirection(Direction::Bottom);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			setDirection(Direction::Left);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			setDirection(Direction::Right);
		}
	}
	void UpdatePathfinding() {
		m_pathfinding.reset();
		m_pathfinding.set(m_grid, m_head->position, m_apple_position);
	}

	bool PathfindingStep() {
		return m_pathfinding.nextStep();;
	}

	void FinishPathfinding() {
		while (!PathfindingStep());
		setDirection(m_pathfinding.nextDirection());
	}


private:
	/*donne une nouvelle position a la pomme*/
	void NewApplePosition() {
		bool found = false;
		sf::Vector2i position;
		while (!found) {
			position = sf::Vector2i(rand() % (m_dimension.x - 2) + 1, rand() % (m_dimension.y - 2) + 1);
			found = (position != m_apple_position && can_move_to(m_grid, position, 0));
		}
		m_apple_position = position;
		std::cout << "Apple : " << position.x << " | " << position.y << std::endl;
	}

protected:
	Direction m_next_direction;
	sf::Vector2i m_dimension;
	sf::Vector2i m_apple_position;
	SnakePart* m_head;
	SnakePart* m_tail;
	std::vector<std::vector<SnakePart*>> m_grid;
	PathfindingAlgorithm m_pathfinding;
};
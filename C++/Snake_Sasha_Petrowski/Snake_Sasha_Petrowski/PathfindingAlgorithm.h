#pragma once
#include <SFML/Graphics.hpp>

#include "SnakePart.h"


struct cell {
	Direction s_direction;
	int s_distance;
};

struct to_visit {
	Direction s_direction;
	sf::Vector2i s_position;
};

class PathfindingAlgorithm {
public:
	PathfindingAlgorithm() {

	}
	PathfindingAlgorithm(std::vector<std::vector<SnakePart*>>& _grid) {
		m_snake_grid = _grid;
		m_path_grid.resize(m_snake_grid.size());
		for (int x = 0; x < m_snake_grid.size(); x++) {
			m_path_grid[x].resize(m_snake_grid[x].size());
		}
		reset();
	};

	void reset() {
		m_to_visit.clear();
		m_path.clear();
		m_reached_goal = false;
		m_backtracked = false;
		m_unreachable = false;

		for (int x = 0; x < m_snake_grid.size(); x++) {
			for (int y = 0; y < m_snake_grid[y].size(); y++) {
				m_path_grid[x][y] = cell();
				m_path_grid[x][y].s_distance = RAND_MAX;
			}
		}

	}

	void set(std::vector<std::vector<SnakePart*>>& _grid, const sf::Vector2i& start, const sf::Vector2i& goal) {
		m_snake_grid = _grid;
		m_goal = goal;
		m_start = start;
		m_to_visit.push_back(to_visit{ m_snake_grid[m_start.x][m_start.y]->direction, m_start });

		m_path_grid[m_start.x][m_start.y].s_direction = m_snake_grid[m_start.x][m_start.y]->direction;
		m_path_grid[m_start.x][m_start.y].s_distance = 0;

		m_path.push_back(m_goal);
	}

	bool nextStep() {
		if (!m_unreachable) {
			if (!m_reached_goal) {
				djikstra();
			}
			else if (!m_backtracked) {
				backtrack();
			}
		}
		return (m_reached_goal && m_backtracked) || m_unreachable;
	}

	Direction nextDirection() {
		if (!m_unreachable) {
			return m_path_grid[m_path[m_path.size() - 1].x][m_path[m_path.size() - 1].y].s_direction;
		}
		else {
			return m_snake_grid[m_start.x][m_start.y]->direction;
		}
	}

	void djikstra() {
		std::cout << "Djikstra." << std::endl;
		if (m_to_visit.size() > 0) {
			to_visit visit = m_to_visit[0];
			m_to_visit.erase(m_to_visit.begin());

			sf::Vector2i position = visit.s_position;
			const std::vector<Direction> directions = SnakePart::DirectionToPossibleDirections(m_path_grid[position.x][position.y].s_direction);
			for (int i = 0; i < directions.size(); i++) {
				sf::Vector2i next_position = position - SnakePart::DirectionToVector(directions[i]);
				if (can_move_to(m_snake_grid, next_position, m_path_grid[position.x][position.y].s_distance + 1) && m_path_grid[next_position.x][next_position.y].s_distance - 1 > m_path_grid[position.x][position.y].s_distance) {
					m_to_visit.push_back(to_visit{ directions[i], next_position });

					m_path_grid[next_position.x][next_position.y].s_direction = directions[i];
					m_path_grid[next_position.x][next_position.y].s_distance = m_path_grid[position.x][position.y].s_distance + 1;

					if (next_position.x == m_goal.x && next_position.y == m_goal.y) {
						m_reached_goal = true;
					}
				}
			}
		}
		else {
			m_unreachable = true;
			std::cout << "ne peut pas atteindre le PathfindingGoal." << std::endl;
		}
	}

	void backtrack() {
		std::cout << "Backtrack." << std::endl;
		sf::Vector2i position = m_path[m_path.size() - 1];
		std::cout << "position set" << std::endl;
		const std::vector<Direction> directions = SnakePart::DirectionToPossibleDirections(SnakePart::InveverseOf(m_path_grid[position.x][position.y].s_direction));
		std::cout << "directions set" << std::endl;
		bool found = false;
		if (position.x == m_start.x && position.y == m_start.y) {
			found = true;
			m_backtracked = true;
		}
		for (int i = 0; i < directions.size(); i++) {
			if (!found) {
				std::cout << "for direction " << i << std::endl;
				sf::Vector2i next_position = position - SnakePart::DirectionToVector(directions[i]);
				if (inbounds(m_snake_grid, next_position) && m_path_grid[next_position.x][next_position.y].s_distance < m_path_grid[position.x][position.y].s_distance) {
					found = true;

					if (next_position.x == m_start.x && next_position.y == m_start.y) {
						m_backtracked = true;
					}
					else {
						m_path.push_back(next_position);
					}
				}
			}
		}
	}
	/*retourne true si la position est dans les limites de la dimension, false sinon.*/
	bool inbounds(const std::vector<std::vector<SnakePart*>>& _grid, const sf::Vector2i& position) {
		return (position.x > 0 && position.y > 0 && position.x < _grid.size() - 1 && position.y < _grid[0].size() - 1);
	}

	/*retourne true si le snake peut aller sur la case en paramètre, false sinon.*/
	bool can_move_to(const std::vector<std::vector<SnakePart*>>& _grid, const sf::Vector2i& position, int distance) {
		return (inbounds(_grid, position) && ((_grid[position.x][position.y] == NULL) || (_grid[position.x][position.y]->distance - distance) < 0));
	}
protected:
	std::vector<std::vector<SnakePart*>> m_snake_grid;
	std::vector<std::vector<cell>> m_path_grid;

	std::vector<to_visit> m_to_visit;
	std::vector<sf::Vector2i> m_path;

	sf::Vector2i m_goal;
	sf::Vector2i m_start;

	bool m_reached_goal;
	bool m_backtracked;
	bool m_unreachable;
};
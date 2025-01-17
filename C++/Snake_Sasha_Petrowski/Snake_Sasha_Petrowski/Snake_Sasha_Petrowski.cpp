#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <iostream>
#include <string>

#include "TileMap.h"
#include "Snake.h"
#include "SnakePart.h"
#include "PathfindingAlgorithm.h"

#define TILESIZE sf::Vector2i(64,64)

/*Pour une raison inconnue le programme a tendance a crash quand on change DIMENSION ou STARTSIZE, on peut les changer, mais certaines valeurs font crasher le programe ¯\_('')_/¯ */
#define DIMENSION sf::Vector2i(20,15)
#define STARTSIZE 4

#define GAMESPEED 0.33

sf::Clock snakeClock;
TileMap tilemap;
Snake   snake;
bool automatic;

std::vector<std::vector<int>> TerrainTiles() {
	std::vector<std::vector<int>> tiles;
	tiles.resize(DIMENSION.x);
	for (int x = 0; x < DIMENSION.x; x++) {
		tiles[x].resize(DIMENSION.y);
		for (int y = 0; y < DIMENSION.y; y++) {
			if (x == 0 || y == 0 || x == DIMENSION.x - 1 || y == DIMENSION.y - 1) {
				tiles[x][y] = 10;
			}
			else {
				tiles[x][y] = 11;
			}
		}
	}
	return tiles;
}

void consoleSnake() {
	std::vector<std::vector<int>> snaketiles = snake.GridToTiles();
	for (int y = 0; y < DIMENSION.y; y++) {
		for (int x = 0; x < DIMENSION.x; x++) {
			if (snaketiles[x][y] != 6) {
				if (snaketiles[x][y] < 10) std::cout << " " << snaketiles[x][y];
				else std::cout << snaketiles[x][y];
			}
			else if (x == 0 || y == 0 || x == DIMENSION.x - 1 || y == DIMENSION.y - 1) {
				std::cout << " X";
			}
			else {
				std::cout << " .";
			}
		}
		std::cout << std::endl;
	}
}

bool UpdateSnake() {
	if (automatic) {
		snake.PathfindingStep();
	}
	if (snakeClock.getElapsedTime().asSeconds() > GAMESPEED) {
		std::cout << "clock" << std::endl;
		snakeClock.restart();
		if (automatic) {
			snake.FinishPathfinding();
		}
		if (snake.Move()) {
			tilemap.update(tilemap.Snake_array, snake.GridToTiles());
			if (automatic) {
				snake.UpdatePathfinding();
			}
			//consoleSnake();
			return true;
		}
		else {
			std::cout << "GAME OVER" << std::endl;
			return false;
		}
	}
	return true;
}

int main()
{
	srand(time(NULL));

	char form;
	do
	{
		std::cout << "Mode automatique ? [y/n]" << std::endl;
		std::cin >> form;
	} while (!std::cin.fail() && form != 'y' && form != 'n');
	automatic = (form == 'y');

	tilemap = TileMap("tilemap.png", TILESIZE, DIMENSION);
	snake   = Snake(STARTSIZE, DIMENSION, automatic);

	tilemap.load(tilemap.Snake_array, snake.GridToTiles());
	tilemap.load(tilemap.Terrain_array, TerrainTiles());

	sf::RenderWindow window(sf::VideoMode(DIMENSION.x * TILESIZE.x, DIMENSION.y * TILESIZE.y), "Snake");
	bool alive = true;
	while (window.isOpen()) {
		// Gestion des évènements
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (!automatic && event.type == sf::Event::KeyPressed)
				snake.keyboard_event();
		}
		if (alive) {
			window.draw(tilemap);
			window.display();
			window.clear();

			alive = UpdateSnake();
		}
	}

	consoleSnake();

	return 0;
}


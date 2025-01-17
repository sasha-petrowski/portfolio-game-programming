#pragma once
#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable {
public:
	TileMap() {

	}
	TileMap(const std::string& _tileset, const sf::Vector2i& _tilesize, const sf::Vector2i& _dimension) {
		m_tilesize = _tilesize;
		m_dimension = _dimension;

		if (!m_tileset.loadFromFile(_tileset)) {
			throw std::runtime_error("Impossible de charger le fichier");
		}
		this->Terrain_array.setPrimitiveType(sf::Quads);
		this->Terrain_array.resize(4 * _dimension.x * _dimension.y);

		this->Snake_array.setPrimitiveType(sf::Quads);
		this->Snake_array.resize(4 * _dimension.x * _dimension.y);
	}
	
	void load(sf::VertexArray& _array, const std::vector<std::vector<int>>& tiles) {
		for (unsigned int x = 0; x < this->m_dimension.x; x++) {
			for (unsigned int y = 0; y < this->m_dimension.y; y++) {
				sf::Vertex* quad = &_array[(x + y * this->m_dimension.x) * 4];
				// Les instructions pour chaque quad...
				quad[0].position = sf::Vector2f( x      * this->m_tilesize.x,  y      * this->m_tilesize.y);
				quad[1].position = sf::Vector2f((x + 1) * this->m_tilesize.x,  y      * this->m_tilesize.y);
				quad[2].position = sf::Vector2f((x + 1) * this->m_tilesize.x, (y + 1) * this->m_tilesize.y);
				quad[3].position = sf::Vector2f( x      * this->m_tilesize.x, (y + 1) * this->m_tilesize.y);

				texture(_array, tiles[x][y], sf::Vector2i(x, y));
			}
		}
	}

	void update(sf::VertexArray& _array, const std::vector<std::vector<int>>& tiles) {
		for (unsigned int x = 0; x < this->m_dimension.x; x++) {
			for (unsigned int y = 0; y < this->m_dimension.y; y++) {
				texture(_array, tiles[x][y], sf::Vector2i(x, y));
			}
		}
	}

	void texture(sf::VertexArray& _array, int _tilenumber, const sf::Vector2i& _position) {
		int tx = _tilenumber % (this->m_tileset.getSize().x / this->m_tilesize.x);
		int ty = _tilenumber / (this->m_tileset.getSize().x / this->m_tilesize.x);

		sf::Vertex* quad = &_array[(_position.x + _position.y * this->m_dimension.x) * 4];
		quad[0].texCoords = sf::Vector2f( tx      * this->m_tilesize.x,  ty      * this->m_tilesize.y);
		quad[1].texCoords = sf::Vector2f((tx + 1) * this->m_tilesize.x,  ty      * this->m_tilesize.y);
		quad[2].texCoords = sf::Vector2f((tx + 1) * this->m_tilesize.x, (ty + 1) * this->m_tilesize.y);
		quad[3].texCoords = sf::Vector2f( tx      * this->m_tilesize.x, (ty + 1) * this->m_tilesize.y);
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.texture = &m_tileset;

		target.draw(Terrain_array, states);
		target.draw(Snake_array, states);
	}

protected:
	sf::Texture m_tileset;
	sf::Vector2i m_tilesize;
	sf::Vector2i m_dimension;

public :
	sf::VertexArray Terrain_array;
	sf::VertexArray Snake_array;
};
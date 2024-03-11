#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Block
{
	sf::Vector2i position;
	sf::RectangleShape rect;
	sf::Texture texture;

public:
	Block(sf::Vector2i _pos)
	{
		rect.setSize(sf::Vector2f(25, 25));
		position = _pos;
		texture.loadFromFile("Data/textures/block_1.png");
		rect.setPosition(_pos.x * 25 + 1, _pos.y * 25 + 1);
		rect.setTexture(&texture);
	}

	void setPosition(sf::Vector2i _pos)
	{
		position.x = _pos.x;
		position.y = _pos.y;
		rect.setPosition(_pos.x * 25 + 1, _pos.y * 25 + 1);
	}

	sf::Vector2i getPosition() { return position; }

	void draw(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
};


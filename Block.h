#pragma once
#include "GlobalVariables.h"

class Block
{
	sf::Vector2i position;
	sf::RectangleShape rect;

public:
	Block(sf::Vector2i _pos, sf::Texture* _tex)
	{
		rect.setSize(sf::Vector2f(25, 25));
		position = _pos;
		rect.setPosition(_pos.x * 25 + 1, _pos.y * 25 + 1);
		rect.setTexture(_tex);
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


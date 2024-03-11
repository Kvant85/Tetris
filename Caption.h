#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Caption
{
	sf::Font font;
	sf::Text text;

public:
	Caption()
	{
		font.loadFromFile("Data/font.TTF");
		text.setFont(font);
		text.setCharacterSize(25);
		text.setFillColor(sf::Color(200, 200, 200));
	}

	void setPosition(sf::Vector2f position) { text.setPosition(position); }
	void setText(string t) { text.setString(t); }
	void setSize(int size) { text.setCharacterSize(size); }
	void setColor(sf::Color color)
	{
		text.setFillColor(color);
		text.setOutlineColor(sf::Color(255, 255, 255));
		text.setOutlineThickness(1.5f);
	}

	sf::Text getText() { return text; }
};
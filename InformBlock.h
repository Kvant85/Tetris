#pragma once
#include "Caption.h"
#include "Block.h"

class InformBlock
{
	sf::Texture frameTex;
	sf::RectangleShape rectFrame;
	Caption titleText, infoText, looseText, winText;
	int nextFigureType;	//Тип следующей фигуры
	vector<Block*> nextBlock;	//Блоки следующей фигуры

public:
	InformBlock()
	{
		srand(std::time(nullptr));
		nextFigureType = rand() % 14;

		//Рамка фигуры
		frameTex.loadFromFile("Data/textures/information.png");
		rectFrame.setSize(sf::Vector2f(175, 150));
		rectFrame.setTexture(&frameTex);
		rectFrame.setPosition(sf::Vector2f(302, 50));

		//Текст заголовка рамки
		titleText.setText("NEXT FIGURE:");
		titleText.setPosition(sf::Vector2f(302, 15));

		//Текст проигрыша
		looseText.setText("GAME OVER");
		looseText.setColor(sf::Color(255, 0, 0));
		looseText.setPosition(sf::Vector2f(322, 110));

		//Текст победы
		winText.setText("YOU WIN!");
		winText.setColor(sf::Color(0, 145, 255));
		winText.setPosition(sf::Vector2f(330, 110));
	}

	void setNextFigureType(int _type, vector<sf::Vector2i> newBlocks)
	{
		nextFigureType = _type;
		nextBlock.erase(nextBlock.begin(), nextBlock.end());
		for (sf::Vector2i b : newBlocks)
		{
			if (_type == 0) nextBlock.push_back(new Block(sf::Vector2i(b.x + 10, b.y + 4.2)));
			else if (_type == 1) nextBlock.push_back(new Block(sf::Vector2i(b.x + 9.5, b.y + 4.2)));
			else if (_type == 2) nextBlock.push_back(new Block(sf::Vector2i(b.x + 10, b.y + 3.7)));
			else if (_type == 3 || _type == 4 || _type == 9 || _type == 10) nextBlock.push_back(new Block(sf::Vector2i(b.x + 9, b.y + 3.7)));
			else if (_type == 5 || _type == 6 || _type == 7 || _type == 8) nextBlock.push_back(new Block(sf::Vector2i(b.x + 9.5, b.y + 3.2)));
			else if (_type == 11) nextBlock.push_back(new Block(sf::Vector2i(b.x + 10, b.y + 3)));
			else if (_type == 12) nextBlock.push_back(new Block(sf::Vector2i(b.x + 8.5, b.y + 4.2)));
			else if (_type == 13) nextBlock.push_back(new Block(sf::Vector2i(b.x + 9.5, b.y + 3.7)));
		}

	}
	int getNextFigure() { return nextFigureType; }

	void draw(sf::RenderWindow* window, int score, int level, int gameState)
	{
		//Будущая фигура
		window->draw(titleText.getText());
		window->draw(rectFrame);	//Рамка фигуры		
		if (gameState != 4 && gameState != 5)
			for (Block* b : nextBlock)
				b->draw(window);	//Фигура

		//Уровень
		infoText.setText("Level: " + to_string(level));
		infoText.setPosition(sf::Vector2f(302, 210));
		window->draw(infoText.getText());

		//Счёт
		infoText.setText("Score: " + to_string(score));
		infoText.setPosition(sf::Vector2f(302, 235));
		window->draw(infoText.getText());

		//Отрисовка проигрыша
		if (gameState == 4)
			window->draw(looseText.getText());

		//Отрисовка победы
		if (gameState == 5)
			window->draw(winText.getText());
	}
};


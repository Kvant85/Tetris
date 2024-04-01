//Функции
#include "GameLogic.h"
//Классы
#include "GameField.h"
#include "InformBlock.h"
#include "GlobalVariables.h"

GameField gameField(sf::Vector2i(11, 20));
InformBlock informBlock;
int gameState = 1;
// 0 - игра, падает блок
// 1 - проверка на полные полосы
// 2 - блок установился - ждём следующий
// 3 - падение активных блоков после нажатия пробела
// 4 - проигрыш
// 5 - победа (миллион очков)
int score = 0;
int level = 1;
float gameSpeed = 0.8f;
sf::Clock gameTimer;

void key_pressing(sf::Event event, sf::RenderWindow* window)
{
	//Закрытие игры
	if (event.key.code == sf::Keyboard::Escape) window->close();

	if (event.type == sf::Event::KeyPressed && gameState == 0)
	{
		if (event.key.code == sf::Keyboard::Up)	//Вращение
			gameField.turnFigure();
		else if (event.key.code == sf::Keyboard::Down)
			gameField.moveActiveBlocks(sf::Vector2i(0, 1));
		else if (event.key.code == sf::Keyboard::Left)
			gameField.moveActiveBlocks(sf::Vector2i(-1, 0));
		else if (event.key.code == sf::Keyboard::Right)
			gameField.moveActiveBlocks(sf::Vector2i(1, 0));
		else if (event.key.code == sf::Keyboard::Space)	//Падение активных блоков в самый низ
			gameState = 3;
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(11 * 25 + 222, 20 * 25 + 2), "Tetris", sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Закрытие окна
			if (event.type == sf::Event::Closed) window.close();
			//Нажатие кнопок
			key_pressing(event, &window);
		}

		window.clear();

		//Игровая логика
		GameLogic(&gameField, &informBlock, &gameTimer, &gameSpeed, &gameState, &score, &level);

		//Отрисовка
		gameField.drawField(&window);
		informBlock.draw(&window, score, level, gameState);

		window.display();
	}
}
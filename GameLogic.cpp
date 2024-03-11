#include "GameLogic.h"

void generateFigure(int _pattern, vector<sf::Vector2i>* newBlocks)
{
	switch (_pattern)
	{
		//Генерация фигуры
	case 0:
		newBlocks->push_back(sf::Vector2i(5, 0));
		break;
	case 1:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(6, 0));
		break;
	case 2:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		break;
	case 3:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(7, 0));
		newBlocks->push_back(sf::Vector2i(6, 1));
		break;
	case 4:
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(7, 1));
		break;
	case 5:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(5, 2));
		break;
	case 6:
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(6, 2));
		break;
	case 7:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(6, 2));
		break;
	case 8:
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(5, 2));
		break;
	case 9:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(6, 1));
		newBlocks->push_back(sf::Vector2i(7, 1));
		break;
	case 10:
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(7, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		break;
	case 11:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(5, 2));
		newBlocks->push_back(sf::Vector2i(5, 3));
		break;
	case 12:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(7, 0));
		newBlocks->push_back(sf::Vector2i(8, 0));
		break;
	case 13:
		newBlocks->push_back(sf::Vector2i(5, 0));
		newBlocks->push_back(sf::Vector2i(6, 0));
		newBlocks->push_back(sf::Vector2i(5, 1));
		newBlocks->push_back(sf::Vector2i(6, 1));
		break;
	}
}

void createFigure(GameField* gameField, InformBlock* infoBlock, int* gameState)
{
	int activeBlocks = 0;
	vector<sf::Vector2i> newBlocks;
	//Тип фигуры
	int pattern = infoBlock->getNextFigure();
	generateFigure(pattern, &newBlocks);
	activeBlocks = newBlocks.size();
	for (sf::Vector2i b : newBlocks)
	{
		//Проверяем, что фигуру можно разместить
		if (gameField->getBlockExistance(b))
		{
			//И если нельзя - это проигрыш
			*gameState = 4;
			return;
		}
	}
	//А если можно - размещаем фигуру на поле
	for (sf::Vector2i b : newBlocks)
		gameField->addBlock(b);
	gameField->setFigureType(pattern, activeBlocks);

	//Устанавливаем тип следующшей фигуры
	int nextPattern = rand() % 14;
	vector<sf::Vector2i> nextFigure;
	generateFigure(nextPattern, &nextFigure);
	infoBlock->setNextFigureType(nextPattern, nextFigure);

	*gameState = 0;
}

void setLevel(float* gameSpeed, int* level, int score, int* gameState)
{
	if (score < 200) *level = 1;
	else if (score >= 200 && score < 1000)
	{
		*level = 2;
		*gameSpeed = 0.7f;
	}
	else if (score >= 1000 && score < 2500)
	{
		*level = 3;
		*gameSpeed = 0.6f;
	}
	else if (score >= 2500 && score < 4000)
	{
		*level = 4;
		*gameSpeed = 0.5f;
	}
	else if (score >= 4000 && score < 6250)
	{
		*level = 5;
		*gameSpeed = 0.4f;
	}
	else if (score >= 6250 && score < 10000)
	{
		*level = 6;
		*gameSpeed = 0.3f;
	}
	else if (score >= 10000 && score < 14000)
	{
		*level = 7;
		*gameSpeed = 0.25f;
	}
	else if (score >= 14000 && score < 20000)
	{
		*level = 8;
		*gameSpeed = 0.2f;
	}
	else if (score >= 20000 && score < 30000)
	{
		*level = 9;
		*gameSpeed = 0.15f;
	}
	else if (score >= 50000 && score < 1000000)
	{
		*level = 10;
		*gameSpeed = 0.1f;
	}
	else if (score >= 1000000) *gameState = 5;
}

void GameLogic(GameField* gameField, InformBlock* infoBlock, sf::Clock* gameTimer, float* gameSpeed, int* gameState, int* score, int* level)
{
	// 0 - игра, падает блок
	if (*gameState == 0 && gameTimer->getElapsedTime().asSeconds() >= *gameSpeed)
	{
		//Активные блоки падают каждый ход пока внизу не появится препятствие (блок или граница)
		if (gameField->fallingActiveBlocks()) *gameState = 1;	//Все блоки походили, меняем статус игры на проверку полос	
		gameTimer->restart();
	}

	//1 - проверяем на полные полосы
	else if (*gameState == 1)
	{
		//Поиск линии
		bool lineFound = true;
		for (int i = 0; i < gameField->getFieldSize().y; i++)
		{
			for (int j = 0; j < gameField->getFieldSize().x; j++)
			{
				if (!gameField->getBlockExistance(sf::Vector2i(j, i)))
				{
					lineFound = false;
					break;
				}
				else lineFound = true;
			}
			if (lineFound)
			{
				//Нашли линию
				for (int k = 0; k < gameField->getFieldSize().x; k++)
				{
					//Удаляем линию
					gameField->removeBlock(sf::Vector2i(k, i));
				}
				//Добавляем удалённые блоки к счёту
				*score += static_cast<int>(gameField->getFieldSize().x * *level / *gameSpeed);
				//Сбрасываем все статичные блоки сверху на 1 клетку ниже
				for (int m = i - 1; m >= 0; m--)
					gameField->moveLine(m);
			}
		}

		//Меняем счёт и устанавливаем уровень игры
		*score += static_cast<int>(gameField->getActiveBlockNumber() * *level / *gameSpeed);
		setLevel(gameSpeed, level, *score, gameState);

		//Полосы проверены, полные удалены, верхние блоки смещены, меняем статус игры на создание блока
		*gameState = 2;
	}

	// 2 - игра, блок установился - ждём и генерируем следующий блок
	else if (*gameState == 2 && gameTimer->getElapsedTime().asSeconds() >= 0.5f)
	{
		createFigure(gameField, infoBlock, gameState);
		gameTimer->restart();
	}

	// 3 - падение активных блоков после нажатия пробела
	else if (*gameState == 3)
	{
		if (gameField->fallingActiveBlocks()) *gameState = 1;
	}
}
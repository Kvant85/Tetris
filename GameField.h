#pragma once
#include "Block.h"

class GameField
{
	sf::Vector2i size;	//������ �������� ����
	vector<Block*> block;	//����������� �����
	vector<Block*> activeBlock;	//�������� �����
	int figureType;	//��� ������� ������
	int activeBlockNumber;	//����� �������� ������

	sf::Texture texture;
	sf::RectangleShape rect;

public:
	GameField(sf::Vector2i _size) : size(_size)
	{
		texture.loadFromFile("Data/textures/fieldBorder.png");
		rect.setSize(sf::Vector2f(277, 502));
		rect.setTexture(&texture);
		rect.setPosition(sf::Vector2f(0, 0));
	}

	//Set
	void setFigureType(int _type, int _blocks)
	{ 
		figureType = _type; 
		activeBlockNumber = _blocks; 
	}

	//Get
	sf::Vector2i getFieldSize() { return size; }
	vector<Block*>* getBlocks() { return &block; }
	int getActiveBlockNumber() { return activeBlockNumber; }

	//�������� �����
	void addBlock(sf::Vector2i _pos)
	{
		activeBlock.push_back(new Block(_pos));
	}

	//�������� �����
	void removeBlock(sf::Vector2i _pos)
	{
		for (Block* b : block)
			if (b->getPosition() == _pos)
			{
				block.erase(remove(block.begin(), block.end(), b));
				break;
			}
	}

	//�������� �������� ������
	void turnFigure()
	{
		if (figureType == 1)
		{
			if (activeBlock.at(0)->getPosition().y + 1 < size.y &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y + 1)))
			{
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y + 1));
				figureType = 2;
			}
		}
		else if (figureType == 2)
		{
			if (activeBlock.at(0)->getPosition().x + 1 < size.x &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)))
			{
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
				figureType = 1;
			}
			else if ((getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)) ||
					activeBlock.at(0)->getPosition().x + 1 == size.x) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)))				
			{
				//���������� ����� - ������ �����������
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1));
				figureType = 1;
			}
			
		}
		else if (figureType == 3)
		{
			if (activeBlock.at(3)->getPosition().y + 1 < size.y)				
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y + 1)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y)))
				{
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y + 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y + 1));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y + 1));
					figureType = 5;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y + 1)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y + 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y + 1));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y + 1));
				figureType = 5;
			}
		}
		else if (figureType == 4)
		{
			if (activeBlock.at(0)->getPosition().y > 0)
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y - 1)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y - 1));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y - 1));
					figureType = 6;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y - 1)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y - 1));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y - 1));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y));
				figureType = 6;
			}
		}
		else if (figureType == 5)
		{
			if (activeBlock.at(3)->getPosition().x + 2 < size.x)
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y + 1)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y + 1)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y + 1));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y + 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y + 1));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 2, activeBlock.at(3)->getPosition().y));
					figureType = 4;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y + 1));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y + 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y + 1));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y));
				figureType = 4;
			}
		}
		else if (figureType == 6)
		{
			if (activeBlock.at(1)->getPosition().x > 0)
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y - 1)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 2, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y - 1));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y - 1));
					figureType = 3;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y - 1));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y - 1));
				figureType = 3;
			}
		}
		else if (figureType == 7)
		{
			if (activeBlock.at(2)->getPosition().x + 1 < size.x)
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 2, activeBlock.at(0)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 2, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y - 1));
					figureType = 10;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y)))
			{
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 2, activeBlock.at(2)->getPosition().y));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y - 1));
				figureType = 10;			
			}
		}
		else if (figureType == 8)
		{
			if (activeBlock.at(0)->getPosition().x + 1 < size.x)
			{
				if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)) &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 2, activeBlock.at(3)->getPosition().y - 1));
					figureType = 9;
				}
			}
			else if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 2, activeBlock.at(0)->getPosition().y)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 2, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y - 1));
				figureType = 9;
			}
		}
		else if (figureType == 9)
		{
			if (activeBlock.at(2)->getPosition().y + 1< size.y &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y + 1)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y + 1));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 2, activeBlock.at(3)->getPosition().y + 1));
				figureType = 8;
			}
		}
		else if (figureType == 10)
		{
			if (activeBlock.at(3)->getPosition().y + 1 < size.y &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y + 1)))
			{
				activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y));
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 2, activeBlock.at(1)->getPosition().y + 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y + 1));
				figureType = 7;
			}
		}
		//��� ��� ������� ��� ������� ����� ���� ���������, �� ������!
		else if (figureType == 11)
		{
			if (!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x + 1, activeBlock.at(0)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x - 1, activeBlock.at(3)->getPosition().y)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y)))
			{
				if (activeBlock.at(0)->getPosition().x + 3 < size.x)
				{
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x + 1, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x + 2, activeBlock.at(2)->getPosition().y - 2));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 3, activeBlock.at(3)->getPosition().y - 3));
					figureType = 12;
				}
				else if (activeBlock.at(0)->getPosition().x + 2 < size.x &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 1, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x + 1, activeBlock.at(2)->getPosition().y - 2));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 2, activeBlock.at(3)->getPosition().y - 3));
					figureType = 12;
				}
				else if (activeBlock.at(0)->getPosition().x + 1 < size.x &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 2, activeBlock.at(0)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 2, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x, activeBlock.at(2)->getPosition().y - 2));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x + 1, activeBlock.at(3)->getPosition().y - 3));
					figureType = 12;
				}
				else if (activeBlock.at(0)->getPosition().x < size.x &&
					!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x - 3, activeBlock.at(0)->getPosition().y)))
				{
					activeBlock.at(0)->setPosition(sf::Vector2i(activeBlock.at(0)->getPosition().x - 3, activeBlock.at(0)->getPosition().y));
					activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 2, activeBlock.at(1)->getPosition().y - 1));
					activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 1, activeBlock.at(2)->getPosition().y - 2));
					activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x, activeBlock.at(3)->getPosition().y - 3));
					figureType = 12;
				}
			}

		}
		else if (figureType == 12)
		{
			if (activeBlock.at(0)->getPosition().y + 3 < size.y &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y + 3)) &&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y + 2))&&
				!getBlockExistance(sf::Vector2i(activeBlock.at(0)->getPosition().x, activeBlock.at(0)->getPosition().y + 1)))
			{
				activeBlock.at(1)->setPosition(sf::Vector2i(activeBlock.at(1)->getPosition().x - 1, activeBlock.at(1)->getPosition().y + 1));
				activeBlock.at(2)->setPosition(sf::Vector2i(activeBlock.at(2)->getPosition().x - 2, activeBlock.at(2)->getPosition().y + 2));
				activeBlock.at(3)->setPosition(sf::Vector2i(activeBlock.at(3)->getPosition().x - 3, activeBlock.at(3)->getPosition().y + 3));
				figureType = 11;
			}
		}
	}

	//�������� �� ������������� ����� � �������� ����� ����
	bool getBlockExistance(sf::Vector2i _pos)
	{
		for (Block* b : block)
			if (b->getPosition() == sf::Vector2i(_pos.x, _pos.y)) return true;
		return false;
	}

	//����������� ������ ������ ����
	void moveLine(int _line)
	{
		for (Block* b : block)
		{
			if (b->getPosition().y == _line)
				b->setPosition(sf::Vector2i(b->getPosition().x, b->getPosition().y + 1));
		}
	}

	//������������ �������� ������
	void moveActiveBlocks(sf::Vector2i _direction)
	{
		//�������� �� ����������� ������������
		bool isDirectionPossible = true;
		for (Block* b : activeBlock)
			if (!(b->getPosition().y + _direction.y < size.y &&	//� �������� ���� (���)
				b->getPosition().x + _direction.x < size.x &&	//� �������� ���� (�����)
				b->getPosition().x + _direction.x >= 0 &&	//� �������� ���� (����)
				getBlockData(b->getPosition(), _direction)))	//�� �������� � ����
			{
				isDirectionPossible = false;
				break;
			}
		//������������
		if (isDirectionPossible)
			for (Block* b : activeBlock)
				b->setPosition(sf::Vector2i(b->getPosition().x + _direction.x, b->getPosition().y + _direction.y));
	}

	//������� �������� ������
	bool fallingActiveBlocks()
	{
		//�������� �� ����������� �������
		bool isDirectionPossible = true;
		for (Block* b : activeBlock)
			if (!(b->getPosition().y < size.y - 1 &&	//� �������� ���� (���)
				getBlockData(b->getPosition(), sf::Vector2i(0, 1))))	//�� �������� � ����
			{
				isDirectionPossible = false;
				//��������� �������� ����� � ����������
				for (Block* b : activeBlock)
					block.push_back(b);
				activeBlock.erase(activeBlock.begin(), activeBlock.end());
				return true;
			}
		//�������
		if (isDirectionPossible)
			for (Block* b : activeBlock)
				b->setPosition(sf::Vector2i(b->getPosition().x, b->getPosition().y + 1));
		return false;
	}

	//��������� ������ �� ����������� �������� ����� (true - �����, false - ���� ������ ��������������)
	bool getBlockData(sf::Vector2i _pos, sf::Vector2i _direction)
	{
		for (Block* b : block)
			if (b->getPosition() == sf::Vector2i(_pos.x + _direction.x, _pos.y + _direction.y))
				return false;
		return true;
	}

	//���������
	void drawField(sf::RenderWindow* window)
	{
		//��������� ������ ����
		window->draw(rect);

		//��������� ��������� ������
		for (Block* b : block)
			b->draw(window);
		//��������� �������� ������
		for (Block* b : activeBlock)
			b->draw(window);
	}
};
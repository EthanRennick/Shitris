// Tetris Clone
//



#include "stdafx.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

const int numRows = 30;
const int numCols = 10;
const int cellSize = 20;


int grid[numRows][numCols] = { 0 };


sf::Color colorPallet[] = { sf::Color::Blue,sf::Color::Cyan,sf::Color::Green,sf::Color::Red,sf::Color::Yellow, sf::Color::Magenta,sf::Color{ 100,100,100 } };

const int numColors = 7;

sf::Vector2i curTetromino[4], savedTetromino[4];



int tetrominos[7][4][2] =
{
	{ { 2,0 },{ 2,1 },{ 2,2 },{ 2,3 } },
	{ { 0,1 },{ 0,2 },{ 1,2 },{ 1,3 } },
	{ { 1,1 },{ 1,2 },{ 0,2 },{ 0,3 } },
	{ { 1,1 },{ 1,2 },{ 0,2 },{ 1,3 } },
	{ { 0,1 },{ 1,1 },{ 1,2 },{ 1,3 } },
	{ { 1,1 },{ 1,2 },{ 1,3 },{ 0,3 } },
	{ { 0,1 },{ 1,1 },{ 0,2 },{ 1,2 } }
};

bool isSpaceToMoveInto()
{
	for (int i = 0; i < 4; i++)
	{
		if (curTetromino[i].x < 0)
		{
			return false;
		}
		if (curTetromino[i].x >= numCols)
		{
			return false;
		}
		if (curTetromino[i].y >= numRows)
		{
			return false;
		}

		if (grid[curTetromino[i].y][curTetromino[i].x] != 0)
		{
			return false;
		}
	}
	return true;
};

void removeAline(int currentRow)
{
	for (int i = currentRow - 1; i > 0; i--)
	{
		for (int col = 0; col < numCols; col++)
		{
			grid[i + 1][col] = grid[i][col];
		}

	}
	for (int col = 0; col < numCols; col++)
	{
		grid[0][col] = grid[0][col];
	}
}
int main()
{


	sf::RenderWindow window(sf::VideoMode(numCols * cellSize, numRows * cellSize), "Tetris");


	srand(time(NULL));

	sf::RectangleShape block;
	block.setSize(sf::Vector2f(cellSize, cellSize));

	int xMoveTetromino = 0;
	bool rotateTetromino = 0;
	int colorNum = 1;
	int curTetrominoIndex = -1;
	colorNum = rand() % numColors;



	curTetrominoIndex = rand() % 7;

	for (int i = 0; i < 4; i++)
	{
		curTetromino[i].x = tetrominos[curTetrominoIndex][i][0];
		curTetromino[i].y = tetrominos[curTetrominoIndex][i][1];
	}
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;

	clock.restart();
	int keypressPause = 0;
	int movePause = 0;
	while (window.isOpen())
	{



		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();


		}
		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{

			if (keypressPause > 0)
			{
				keypressPause--;
			}
			if (keypressPause == 0)
			{
				keypressPause = 4;

				if (curTetrominoIndex != 6)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						for (int i = 0; i < 4; i++)
						{
							savedTetromino[i] = curTetromino[i];

						}
						//rotate the tetromino

						sf::Vector2i centerOfTetromino = curTetromino[1];

						for (int i = 0; i < 4; i++)
						{
							int diffY = curTetromino[i].y - centerOfTetromino.y;
							int diffX = curTetromino[i].x - centerOfTetromino.x;
							curTetromino[i].x = centerOfTetromino.x - diffY;
							curTetromino[i].y = centerOfTetromino.y + diffX;
						}
						if (!isSpaceToMoveInto())
						{
							for (int i = 0; i < 4; i++)
							{
								curTetromino[i] = savedTetromino[i];
							}
						}
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					xMoveTetromino = -1;
					for (int i = 0; i < 4; i++)
					{
						savedTetromino[i] = curTetromino[i];
					}
					for (int i = 0; i < 4; i++)
					{
						curTetromino[i].x += xMoveTetromino;
					}
					if (!isSpaceToMoveInto())
					{
						for (int i = 0; i < 4; i++)
						{
							curTetromino[i] = savedTetromino[i];
						}
					}

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					xMoveTetromino = 1;

					for (int i = 0; i < 4; i++)
					{
						savedTetromino[i] = curTetromino[i];

					}
					for (int i = 0; i < 4; i++)
					{

						curTetromino[i].x += xMoveTetromino;
					}
					if (!isSpaceToMoveInto())
					{
						for (int i = 0; i < 4; i++)
						{
							curTetromino[i] = savedTetromino[i];
						}
					}

				}

			}


			if (movePause > 0)
			{
				movePause--;
			}
			if (movePause == 0)
			{
				movePause = 8;

				for (int i = 0; i < 4; i++)
				{
					savedTetromino[i] = curTetromino[i];

				}
				for (int i = 0; i < 4; i++)
				{
					curTetromino[i].y += 1;
				}

				if (!isSpaceToMoveInto())
				{
					for (int i = 0; i < 4; i++)
					{
						grid[savedTetromino[i].y][savedTetromino[i].x] = colorNum;
					}

					colorNum = 1 + rand() % numColors;
					curTetrominoIndex = rand() % 7;

					for (int i = 0; i < 4; i++)
					{
						curTetromino[i].x = tetrominos[curTetrominoIndex][i][0];
						curTetromino[i].y = tetrominos[curTetrominoIndex][i][1];
					}
				}


				//remove any filled rows and move all the  rows down one .
				for (int curRow = numRows - 1; curRow >= 0; )
				{
					int count = 0;
					for (int col = 0; col < numCols; col++)
					{
						if (grid[curRow][col])
						{
							count++;
						}
					}
					if (count == numCols)
					{
						removeAline(curRow);
					}
					else {
						curRow--;
					}
				}


			}
			xMoveTetromino = 0;

			rotateTetromino = 0;


			window.clear(sf::Color::Black);

			for (int curRow = 0; curRow < numRows; curRow++)
			{
				for (int curCol = 0; curCol < numCols; curCol++)
				{
					if (grid[curRow][curCol] != 0)
					{

						block.setPosition(curCol * cellSize, curRow * cellSize);
						block.setFillColor(colorPallet[grid[curRow][curCol] - 1]);

						window.draw(block);
					}
				}
			}

			for (int i = 0; i < 4; i++)
			{
				block.setPosition(curTetromino[i].x * cellSize, curTetromino[i].y * cellSize);
				block.setFillColor(colorPallet[colorNum - 1]);
				window.draw(block);
			}


			window.display();

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}



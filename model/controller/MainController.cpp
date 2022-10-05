#include "MainController.h"
#include "../views/GameView.h"

MainController::MainController()
{
	InitializeGame();
	ChangeView(new GameView());
}

void MainController::InitializeGame()
{
	_direction = Direction::RIGHT;
	_canChangeDirection = true;
	int x = 100;

	for (int i = 0; i < 10; i++)
	{
		_snake.emplace_back(SnakePosition(x, 100));
		x -= SNAKE_WIDTH * 2;
	}
}

void MainController::SetDirection(const Direction direction)
{
	if (_canChangeDirection)
	{
		_direction = direction;
		_canChangeDirection = false;
	}
}

void MainController::UpdateSnakePosition()
{
	std::vector<SnakePosition> newPositions = {};

	int i = 0;
	for (const SnakePosition& position : _snake)
	{
		SnakePosition newPosition;

		if (_snake.front() == position)
		{
			if (_direction == Direction::UP)
			{
				newPosition = SnakePosition(position.X, position.Y - SNAKE_WIDTH * 2);
			}
			else if (_direction == Direction::DOWN)
			{
				newPosition = SnakePosition(position.X, position.Y + SNAKE_WIDTH * 2);
			}
			else if (_direction == Direction::LEFT)
			{
				newPosition = SnakePosition(position.X - SNAKE_WIDTH * 2, position.Y);
			}
			else if (_direction == Direction::RIGHT)
			{
				newPosition = SnakePosition(position.X + SNAKE_WIDTH * 2, position.Y);
			}

			newPositions.emplace_back(newPosition);
		}
		else
		{
			newPosition = _snake[i - 1];
			newPositions.emplace_back(newPosition);
		}

		i++;
	}

	for (i = 0; i < static_cast<int>(_snake.size()); i++)
	{
		_snake[i] = newPositions[i];
	}

	_canChangeDirection = true;
}

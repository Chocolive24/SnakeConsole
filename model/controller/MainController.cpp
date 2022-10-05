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
	int x = 20 + SNAKE_START_PARTS * GetSpaceBetweenSnakeParts();

	for (int i = 0; i < SNAKE_START_PARTS; i++)
	{
		_snake.emplace_back(SnakePosition(x, 100));
		x -= GetSpaceBetweenSnakeParts();
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
		if (i == 0)
		{
			SnakePosition newPosition;

			if (_direction == Direction::UP)
			{
				newPosition = SnakePosition(position.X, position.Y - GetSpaceBetweenSnakeParts());
			}
			else if (_direction == Direction::DOWN)
			{
				newPosition = SnakePosition(position.X, position.Y + GetSpaceBetweenSnakeParts());
			}
			else if (_direction == Direction::LEFT)
			{
				newPosition = SnakePosition(position.X - GetSpaceBetweenSnakeParts(), position.Y);
			}
			else if (_direction == Direction::RIGHT)
			{
				newPosition = SnakePosition(position.X + GetSpaceBetweenSnakeParts(), position.Y);
			}

			newPositions.emplace_back(newPosition);
		}
		else
		{
			newPositions.emplace_back(_snake[i - 1]);
		}

		i++;
	}

	for (i = 0; i < static_cast<int>(_snake.size()); i++)
	{
		_snake[i] = newPositions[i];
	}

	_canChangeDirection = true;
}

bool MainController::CanUpdateSnakePosition() const
{
	if (Tick > 0 && CurrentFPS > 0)
	{
		int updatePerTick = CurrentFPS / SNAKE_UPDATE_PER_SECOND;

		if (updatePerTick == 0)
		{
			updatePerTick = 1;
		}

		return Tick % updatePerTick == 0;
	}

	return false;
}

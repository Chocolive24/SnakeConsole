#include "Game.h"
#include "../views/GameView.h"

Game::Game()
{
	InitializeGame();

	ChangeView(new GameView(this));
}

void Game::InitializeGame()
{
	_snake = {};
	_score = 0;
	_lost = false;
	_directionChangeFromLastEgg = 0;
	_combo = 0;
	_direction = Direction::RIGHT;
	_canChangeDirection = true;
	int x = 20 + SNAKE_START_PARTS * GetSpaceBetweenSnakeParts();

	for (int i = 0; i < SNAKE_START_PARTS; i++)
	{
		_snake.emplace_back(Point(x, 100));
		x -= GetSpaceBetweenSnakeParts();
	}

	SpawnEgg();
}

void Game::SetDirection(const Direction direction)
{
	if (_canChangeDirection)
	{
		_direction = direction;
		_canChangeDirection = false;
		_directionChangeFromLastEgg++;
	}
}

void Game::SpawnEgg()
{
	while (true)
	{
		Point potentialEgg = Point(
			10 + Random::GetInt(0, 30) * 10,
			10 + Random::GetInt(0, 30) * 10
		);

		bool valid = true;

		for (Point p: _snake)
		{
			if (p == potentialEgg)
			{
				valid = false;
			}
		}

		if (valid)
		{
			_egg = potentialEgg;
			break;
		}
	}
}

void Game::UpdateSnakePosition()
{
	std::vector<Point> newPositions = {};

	int i = 0;
	for (const Point& position : _snake)
	{
		if (i == 0)
		{
			Point newPosition;

			if (_direction == Direction::UP)
			{
				newPosition = Point(position.X, position.Y - GetSpaceBetweenSnakeParts());
			}
			else if (_direction == Direction::DOWN)
			{
				newPosition = Point(position.X, position.Y + GetSpaceBetweenSnakeParts());
			}
			else if (_direction == Direction::LEFT)
			{
				newPosition = Point(position.X - GetSpaceBetweenSnakeParts(), position.Y);
			}
			else if (_direction == Direction::RIGHT)
			{
				newPosition = Point(position.X + GetSpaceBetweenSnakeParts(), position.Y);
			}

			newPositions.emplace_back(newPosition);
		}
		else
		{
			if (_snake[i] != _snake[i - 1])
			{
				newPositions.emplace_back(_snake[i - 1]);
			}
			else
			{
				newPositions.emplace_back(_snake[i]);
			}

			/*if (newPositions[0] == newPositions.back())
			{
				_lost = true;
			}*/
		}

		i++;
	}

	for (i = 0; i < static_cast<int>(_snake.size()); i++)
	{
		_snake[i] = newPositions[i];
	}

	_canChangeDirection = true;

	if (_snake[0] == _egg)
	{
		_snake.emplace_back(_snake.back());
		SpawnEgg();

		if (_directionChangeFromLastEgg <= 4)
		{
			_combo++;
			_score += 5 * _combo;
		}
		else
		{
			_combo = 0;
		}

		_directionChangeFromLastEgg = 0;
		_score += 10;
	}

	UpdateIA();
}

bool Game::CanUpdateSnakePosition(int deltaTime)
{
	_snakeTime += deltaTime;

	if (1000000000 / SNAKE_UPDATE_PER_SECOND <= _snakeTime)
	{
		_snakeTime = 0;

		return true;
	}

	return false;
}

void Game::UpdateIA()
{
	const Point head = _snake.front();

	if ((_direction == Direction::RIGHT && _egg.X <= head.X) || (_direction == Direction::LEFT && _egg.X >= head.X))
	{
		if (_egg.Y <= head.Y)
		{
			SetDirection(Direction::UP);
		}
		else
		{
			SetDirection(Direction::DOWN);
		}
	}
	else if ((_direction == Direction::UP && _egg.Y >= head.Y) || (_direction == Direction::DOWN && _egg.Y <= head.Y))
	{
		if (_egg.X <= head.X)
		{
			SetDirection(Direction::LEFT);
		}
		else
		{
			SetDirection(Direction::RIGHT);
		}
	}
}

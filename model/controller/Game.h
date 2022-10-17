#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

struct Point
{
	int X{ 0 };
	int Y{ 0 };

	bool operator==(const Point& point) const
	{
		return X == point.X && Y == point.Y;
	}
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Game : public Console::Controller
{
private:
	std::vector<Point> _snake;
	Point _egg;

	Direction _direction;
	bool _canChangeDirection;
	int _snakeTime = 0;
	int _directionChangeFromLastEgg;
	int _combo = 0;

	bool _lost = false;
	int _score = 0;

public:
	Game();

	inline static int SNAKE_WIDTH = 5;
	inline static int SNAKE_UPDATE_PER_SECOND = 20 * 3;
	inline static int SNAKE_START_PARTS = 10;
	static int GetSpaceBetweenSnakeParts() { return static_cast<int>(SNAKE_WIDTH * 2.0f); }

	void InitializeGame();

	std::vector<Point>& GetSnake() { return _snake; }
	Direction GetDirection() const { return _direction; }
	Point& GetEgg() { return _egg; }
	bool HasLost() const { return _lost; }
	int GetScore() { return _score; }
	int GetCombo() { return _combo; }

	void SetDirection(Direction direction);
	void SpawnEgg();

	/**
	 * \brief Update the snake position according to the direction.
	 */
	void UpdateSnakePosition();
	/**
	 * \brief Check if the snake can update its position.
	 * \return true if the snake can update its position, false otherwise.
	 */
	bool CanUpdateSnakePosition(int deltaTime);

	void UpdateIA();
};


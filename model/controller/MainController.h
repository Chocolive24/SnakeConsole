#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

struct SnakePosition
{
	int X{ 0 };
	int Y{ 0 };

	bool operator==(const SnakePosition position) const
	{
		return X == position.X && Y == position.Y;
	}
};

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MainController : public Console::Controller
{
private:
	std::vector<SnakePosition> _snake;
	Direction _direction;
	bool _canChangeDirection;
public:
	MainController();

	inline static int SNAKE_WIDTH = 5;

	void InitializeGame();
	std::vector<SnakePosition>& GetSnake() { return _snake; }
	Direction GetDirection() const { return _direction; }
	void SetDirection(Direction direction);
	void UpdateSnakePosition();
};


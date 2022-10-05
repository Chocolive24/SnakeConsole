#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

struct SnakePosition
{
	int X{ 0 };
	int Y{ 0 };
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
	inline static int SNAKE_UPDATE_PER_SECOND = 20;
	inline static int SNAKE_START_PARTS = 30;
	static int GetSpaceBetweenSnakeParts() { return static_cast<int>(SNAKE_WIDTH * 1.8f); }

	void InitializeGame();
	std::vector<SnakePosition>& GetSnake() { return _snake; }
	Direction GetDirection() const { return _direction; }
	void SetDirection(Direction direction);
	/**
	 * \brief Update the snake position according to the direction.
	 */
	void UpdateSnakePosition();
	/**
	 * \brief Check if the snake can update its position.
	 * \return true if the snake can update its position, false otherwise.
	 */
	bool CanUpdateSnakePosition() const;
};


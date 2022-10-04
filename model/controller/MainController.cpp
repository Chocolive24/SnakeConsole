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
	int x = 100;

	for (int i = 0; i < 5; i++)
	{
		_snake.emplace_back(SnakePosition(x, 100));
		x -= SNAKE_WIDTH * 2;
	}
}

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
	_snake = {
		SnakePosition(10, 1),
		SnakePosition(9, 1),
		SnakePosition(8, 1),
		SnakePosition(7, 1),
		SnakePosition(6, 1),
	};
}

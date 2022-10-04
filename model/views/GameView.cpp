#include "GameView.h"
#include "../controller/MainController.h"

GameView::GameView()
{

}

void GameView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	auto mainController = static_cast<MainController*>(controller);
	std::vector<SnakePosition>& snake = mainController->GetSnake();
	bool mustUpdate = controller->Tick > 0;
	std::vector<SnakePosition> newPositions = {};

	if (mustUpdate)
	{
		mustUpdate = controller->Tick % 2 == 0;
	}

	int i = 0;
	for (const SnakePosition& position: snake)
	{
		if (mustUpdate)
		{
			if (snake.front() == position)
			{
				SnakePosition newPosition;

				if (mainController->GetDirection() == Direction::UP)
				{
					newPosition = SnakePosition(position.X, position.Y - MainController::SNAKE_WIDTH * 2);
				}
				else if (mainController->GetDirection() == Direction::DOWN)
				{
					newPosition = SnakePosition(position.X, position.Y + MainController::SNAKE_WIDTH * 2);
				}
				else if (mainController->GetDirection() == Direction::LEFT)
				{
					newPosition = SnakePosition(position.X - MainController::SNAKE_WIDTH * 2, position.Y);
				}
				else if (mainController->GetDirection() == Direction::RIGHT)
				{
					newPosition = SnakePosition(position.X + MainController::SNAKE_WIDTH * 2, position.Y);
				}

				newPositions.emplace_back(newPosition);
			}
			else
			{
				newPositions.emplace_back(snake[i - 1]);
			}
		}
		
		COLORREF color;

		if (snake.front() == position)
		{
			color = RGB(50, 50, 200);
		}
		else
		{
			color = RGB(60, 60, 230);
		}
		
		screen.DrawCircle(position.X, position.Y, MainController::SNAKE_WIDTH, color);
		i++;
	}

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(controller->CurrentFPS), .X = 1, .Y = 1 });

	if (mustUpdate)
	{
		for (int i = 0;i < snake.size(); i++)
		{
			snake[i] = newPositions[i];
		}
	}
}

void GameView::OnKeyPressed(Console::Controller* controller, char key)
{
	const auto mainController = static_cast<MainController*>(controller);

	if (key == Console::Key::Up && mainController->GetDirection() != Direction::DOWN)
	{
		mainController->SetDirection(Direction::UP);
	}
	else if (key == Console::Key::Down && mainController->GetDirection() != Direction::UP)
	{
		mainController->SetDirection(Direction::DOWN);
	}
	else if (key == Console::Key::Left && mainController->GetDirection() != Direction::RIGHT)
	{
		mainController->SetDirection(Direction::LEFT);
	}
	else if (key == Console::Key::Right && mainController->GetDirection() != Direction::LEFT)
	{
		mainController->SetDirection(Direction::RIGHT);
	}

	View::OnKeyPressed(controller, key);
}

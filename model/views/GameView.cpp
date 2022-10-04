#include "GameView.h"
#include "../controller/MainController.h"

GameView::GameView()
{

}

void GameView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	auto mainController = dynamic_cast<MainController*>(controller);
	std::vector<SnakePosition>& snake = mainController->GetSnake();
	bool mustUpdate = controller->CurrentFPS > 0 && controller->Tick > 0;
	std::vector<SnakePosition> newPositions = {};

	if (mustUpdate)
	{
		if (mainController->GetDirection() == Direction::DOWN || mainController->GetDirection() == Direction::UP)
		{
			mustUpdate = controller->Tick % static_cast<int>(controller->CurrentFPS * 0.05 * 1.25) == 0;
		}
		else
		{
			mustUpdate = controller->Tick % static_cast<int>(controller->CurrentFPS * 0.05) == 0;
		}
	}

	int i = 0;
	for (SnakePosition& position: snake)
	{
		if (mustUpdate)
		{
			if (snake.front() == position)
			{
				SnakePosition newPosition;

				if (mainController->GetDirection() == Direction::UP)
				{
					newPosition = SnakePosition(position.X, position.Y - 1);
				}
				else if (mainController->GetDirection() == Direction::DOWN)
				{
					newPosition = SnakePosition(position.X, position.Y + 1);
				}
				else if (mainController->GetDirection() == Direction::LEFT)
				{
					newPosition = SnakePosition(position.X - 1, position.Y);
				}
				else if (mainController->GetDirection() == Direction::RIGHT)
				{
					newPosition = SnakePosition(position.X + 1, position.Y);
				}

				newPositions.emplace_back(newPosition);
			}
			else
			{
				newPositions.emplace_back(snake[i - 1]);
			}
		}

		Console::Background background;
		COLORREF color;

		if (snake.front() == position)
		{
			background = Console::Background::CYAN;
			color = RGB(50, 50, 200);
		}
		else
		{
			background = Console::Background::WHITE;
			color = RGB(60, 60, 230);
		}

		screen.Draw(Console::PixelColor(position.X, position.Y, color));
		//screen.Draw(Console::Text{ .Str = " ", .X = position.X, .Y = position.Y, .Background = background });
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
	auto mainController = dynamic_cast<MainController*>(controller);

	if (key == Console::Key::Up)
	{
		mainController->SetDirection(Direction::UP);
	}
	else if (key == Console::Key::Down)
	{
		mainController->SetDirection(Direction::DOWN);
	}
	else if (key == Console::Key::Left)
	{
		mainController->SetDirection(Direction::LEFT);
	}
	else if (key == Console::Key::Right)
	{
		mainController->SetDirection(Direction::RIGHT);
	}

	View::OnKeyPressed(controller, key);
}

#include "GameView.h"
#include "../controller/MainController.h"

void GameView::Update(Console::Controller* controller, Console::Screen& screen)
{
	View::Update(controller, screen);

	if (_pause)
	{
		screen.Draw(Console::Text{ .Str = "PAUSE", .X = screen.GetWidth() / 2, .Y = screen.GetHeight() / 2, .Foreground = Console::Foreground::CYAN });
		return;
	}

	const auto mainController = static_cast<MainController*>(controller);
	const std::vector<SnakePosition>& snake = mainController->GetSnake();

	int i = 0;
	for (const SnakePosition& position: snake)
	{
		const COLORREF snakeColor = RGB(70, 70, 255 - 150 / snake.size() * (i+1) );
		
		screen.DrawCircle(position.X, position.Y, MainController::SNAKE_WIDTH, snakeColor, true);
		i++;
	}

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(controller->CurrentFPS), .X = 1, .Y = 1 });

	if (controller->Tick > 0 && controller->Tick % 2 == 0)
	{
		mainController->UpdateSnakePosition();
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

	if (key == Console::Key::Space)
	{
		_pause = !_pause;
	}

	View::OnKeyPressed(controller, key);
}

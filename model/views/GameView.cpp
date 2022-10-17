#include "GameView.h"
#include "../controller/Game.h"

GameView::GameView(Game* game)
{
	_game = game;
	_pause = false;
}

void GameView::Update(Console::Screen& screen)
{
	View::Update(screen);

	screen.Draw(Console::Text{
		.Str = "Score: " + std::to_string(_game->GetScore()) + " pts | Combo x" + std::to_string(_game->GetCombo()),
		.X = PositionX(0.5f).GetValue(),
		.Y = 2,
		.XCentered = true
	});

	if (_pause)
	{
		screen.Draw(Console::Text{
			.Str = "PAUSE",
			.X = PositionX(0.5f).GetValue(),
			.Y = PositionY(0.5f).GetValue(),
			.XCentered = true,
			.Background = Console::Background::WHITE,
			.Foreground = Console::Foreground::CYAN
		});

		return;
	}

	if (_game->HasLost())
	{
		screen.Draw(Console::Text{
			.Str = "You lost !",
			.X = PositionX(0.5f).GetValue(),
			.Y = PositionY(0.5f).GetValue(),
			.XCentered = true,
			.Background = Console::Background::RED,
			.Foreground = Console::Foreground::WHITE
		});

		screen.Draw(Console::Text{
			.Str = "Press R to restart",
			.X = PositionX(0.5f).GetValue(),
			.Y = PositionY(0.75f).GetValue(),
			.XCentered = true
		});
	}

	const std::vector<Point>& snake = _game->GetSnake();

	int i = 0;
	for (const Point& position: snake)
	{
		const COLORREF snakeColor = RGB(70, 70, 255 - 150 / snake.size() * (i+1) );
		
		screen.DrawCircle(position.X, position.Y, Game::SNAKE_WIDTH, snakeColor, true);
		i++;
	}

	constexpr COLORREF eggColor = RGB(200, 200, 200);
	Point egg = _game->GetEgg();

	screen.DrawCircle(egg.X, egg.Y, Game::SNAKE_WIDTH, eggColor, true);

	screen.Draw(Console::Text{ .Str = "FPS: " + std::to_string(Console::Controller::FPS), .X = 1, .Y = 1 });
}

void GameView::OnKeyPressed(char key)
{
	if (key == Console::Key::Up && _game->GetDirection() != Direction::DOWN)
	{
		_game->SetDirection(Direction::UP);
	}
	else if (key == Console::Key::Down && _game->GetDirection() != Direction::UP)
	{
		_game->SetDirection(Direction::DOWN);
	}
	else if (key == Console::Key::Left && _game->GetDirection() != Direction::RIGHT)
	{
		_game->SetDirection(Direction::LEFT);
	}
	else if (key == Console::Key::Right && _game->GetDirection() != Direction::LEFT)
	{
		_game->SetDirection(Direction::RIGHT);
	}

	if (key == Console::Key::Space)
	{
		_pause = !_pause;
	}

	if (_game->HasLost() && key == 'r')
	{
		_game->InitializeGame();
	}

	View::OnKeyPressed(key);
}

void GameView::OnTick(int deltaTime)
{
	if (!_game->HasLost() && !_pause && _game->CanUpdateSnakePosition(deltaTime))
	{
		_game->UpdateSnakePosition();
	}
}

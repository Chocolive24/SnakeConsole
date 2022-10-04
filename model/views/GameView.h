#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

class GameView : public Console::View
{
private:
	bool _pause;

public:
	GameView() = default;

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};


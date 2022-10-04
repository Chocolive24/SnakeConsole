#pragma once
#include "../../libs/ConsoleViewController/ConsoleViewController.h"

class GameView : public Console::View
{
public:
	GameView();

	void Update(Console::Controller* controller, Console::Screen& screen) override;
	void OnKeyPressed(Console::Controller* controller, char key) override;
};


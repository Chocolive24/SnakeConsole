#include "libs/ConsoleViewController/ConsoleViewController.h"
#include "model/controller/Game.h"

int main()
{
    Console::Screen::EnableVirtualTerminalProcessing();
    Console::Screen::SetWindowSize(700, 500);
    Console::Screen::CenterWindow();

    Game game;
    game.Start();
}

#include "libs/ConsoleViewController/ConsoleViewController.h"
#include "model/controller/MainController.h"

int main()
{
    Console::Screen::SetWindowSize(1000, 700);
    Console::Screen::CenterWindow();

    MainController mainController;
    mainController.Start();
}

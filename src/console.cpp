#include "../include/console.hpp"
#include <iostream>

namespace ConsoleUtils
{
    void ShowCursor(bool CursorVisibility)
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
        SetConsoleCursorInfo(handle, &cursor);
    }

    void Gotoxy(SHORT posX, SHORT posY)
    {
        HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD Position;
        Position.X = posX;
        Position.Y = posY;

        SetConsoleCursorPosition(hStdout, Position);
    }

    void ClearLine(SHORT posY)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        Gotoxy(0, posY);
        for (int i = 0; i < consoleWidth; i++)
        {
            std::cout << " ";
        }
        Gotoxy(0, posY);
    }

    void ClearLine(SHORT posX, SHORT posY, SHORT length)
    {
        Gotoxy(posX, posY);
        for (int i = 0; i < length; i++)
        {
            std::cout << " ";
        }
        Gotoxy(posX, posY);
    }
}
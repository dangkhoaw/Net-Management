#ifndef CONSOLE
#define CONSOLE 1

#include <windows.h>

namespace ConsoleUtils
{
    void ShowCursor(bool CursorVisibility);

    void Gotoxy(SHORT posX, SHORT posY);

    void ClearLine(SHORT posY);

    void ClearLine(SHORT posX, SHORT posY, SHORT length);
}

#endif
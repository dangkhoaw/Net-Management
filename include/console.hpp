#ifndef CONSOLE
#define CONSOLE 1

#include <windows.h>
#include "list.hpp"

namespace ConsoleUtils
{
    void ShowCursor(bool CursorVisibility);
    void Gotoxy(SHORT posX, SHORT posY);
    void ClearLine(SHORT posY);
    void ClearLine(SHORT posX, SHORT posY, SHORT length);
    void print(const char *str, List<const char *> attributes = {});
    void error(const char *str);
    void setColor(List<const char *> attributes);
}

#endif
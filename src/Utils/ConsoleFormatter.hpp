#pragma once

namespace ConsoleFormatter
{
    const int RED_CONSOLE_COLOR = 12;
    const int GREEN_CONSOLE_COLOR = 10;
    const int WHITE_CONSOLE_COLOR = 15;

    void SetConsoleColor(int color);
    void ResetConsoleColor();
}
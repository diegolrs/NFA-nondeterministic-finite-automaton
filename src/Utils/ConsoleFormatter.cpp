#include "ConsoleFormatter.hpp"

#define IS_ON_WINDOWS defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#if IS_ON_WINDOWS
    #include <windows.h> // Used to change color of text
#endif

void ConsoleFormatter::SetConsoleColor(int color)
{
#if IS_ON_WINDOWS
    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, color);
#endif
}

void ConsoleFormatter::ResetConsoleColor()
{
    SetConsoleColor(WHITE_CONSOLE_COLOR);
}
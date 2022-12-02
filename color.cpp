#include <iostream>

using namespace std;

#define RED_CONSOLE_COLOR 4
#define GREEN_CONSOLE_COLOR 2
#define WHITE_CONSOLE_COLOR 15

#define IS_ON_WINDOWS defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#if IS_ON_WINDOWS
#include <windows.h> // Used to change color of text
void SetConsoleColor_Windows(int color)
{

    HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, color);
}
#endif

void SetConsoleColor(int color)
{
#if IS_ON_WINDOWS
    SetConsoleColor_Windows(color);
#endif
}

void ResetConsoleColor()
{
    SetConsoleColor(WHITE_CONSOLE_COLOR);
}
  
// Driver Code
int main()
{
    SetConsoleColor(RED_CONSOLE_COLOR);
    cout << " Hello Geeks, " << "good night!!!";

    SetConsoleColor(WHITE_CONSOLE_COLOR);
    cout << " Hello Geeks, " << "good night!!!";

    SetConsoleColor(GREEN_CONSOLE_COLOR);
    cout << " Hello Geeks, " << "good night!!!";

    ResetConsoleColor();
  
    return 0;
}
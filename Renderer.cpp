#include "Renderer.h"
#include <iostream>

ConsoleRenderer::ConsoleRenderer(int w, int h)
    : width(w), height(h)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

void ConsoleRenderer::hideCursor() const
{
    CONSOLE_CURSOR_INFO ci{};
    GetConsoleCursorInfo(hConsole, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &ci);
}

void ConsoleRenderer::clear() const
{
    COORD topLeft = {0, 0};
    SetConsoleCursorPosition(hConsole, topLeft);
}

void ConsoleRenderer::draw(char ch, int x, int y) const
{
    COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(hConsole, pos);
    std::cout << ch;
}

void ConsoleRenderer::draw(const std::string& s) const
{
    std::cout << s;
}
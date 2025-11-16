#pragma once
#include <windows.h>
#include <string>
#include <vector>

class ConsoleRenderer {
public:
    explicit ConsoleRenderer(int w, int h);
    ~ConsoleRenderer() = default;

    void clear() const;                     // move cursor to (0,0)
    void draw(char ch, int x, int y) const; // draw a single cell
    void draw(const std::string& s) const;  // draw a line (ends with \n)
    void hideCursor() const;

private:
    HANDLE hConsole;
    int width, height;
};
#include "Input.h"
#include <cctype>

Key Keyboard::getKey()
{
    if (!_kbhit()) return Key::None;

    int ch = _getch();
    switch (std::tolower(ch)) {
        case 'w': case 72: return Key::Up;      // 72 = VK_UP
        case 's': case 80: return Key::Down;    // 80 = VK_DOWN
        case 'a': case 75: return Key::Left;    // 75 = VK_LEFT
        case 'd': case 77: return Key::Right;   // 77 = VK_RIGHT
        case 'x':          return Key::Quit;
        default:           return Key::None;
    }
}
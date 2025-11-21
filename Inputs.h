#pragma once
#include <conio.h>

enum class Key { None, Up, Down, Left, Right, Quit };

class Keyboard {
public:
    static Key getKey();   // returns Key::None if nothing pressed
};
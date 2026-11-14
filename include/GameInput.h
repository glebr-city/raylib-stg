//
// Created by n on 14/11/2026.
//

#ifndef RAYLIB_STG_GAMEINPUT_H
#define RAYLIB_STG_GAMEINPUT_H
#include <string>
#include <vector>

#include "raylib.h"

class MyKey
{
public:
    KeyboardKey k = KEY_SPACE; //Keys (as on a keyboard).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
    MyKey(const KeyboardKey _k = KEY_SPACE,
    const bool _d = false,
    const bool _l = false,
    const bool _md = false,
    const bool _ml = false)
    {
        k = _k;
        d = _d;
        l = _l;
        md = _md;
        ml = _ml;
    };
};

class MyButton
{
public:
    GamepadButton b = GAMEPAD_BUTTON_RIGHT_FACE_DOWN; //Buttons (as on a gamepad controller).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
    MyButton(const GamepadButton _b = GAMEPAD_BUTTON_RIGHT_FACE_DOWN, const bool _d = false, const bool _l = false, const bool _md = false, const bool _ml = false)
    {
        b = _b;
        d = _d;
        l = _l;
        md = _md;
        ml = _ml;
    };
};

class GameInput
{
public:
    std::string name;
    std::vector<MyKey> keys;
    std::vector<MyButton> buttons;
    GameInput(const std::string _name,
    const std::vector<MyKey> _keys,
    const std::vector<MyButton> _buttons)
    {
        name = _name;
        keys = _keys;
        buttons = _buttons;
    };
};
#endif //RAYLIB_STG_GAMEINPUT_H

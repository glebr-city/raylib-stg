//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "raylib/raylib.h"

struct MyKey
{
    KeyboardKey k = KEY_SPACE; //Keys (as on a keyboard).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
};

struct MyButton
{
    GamepadButton b = GAMEPAD_BUTTON_RIGHT_FACE_DOWN; //Buttons (as on a gamepad controller).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
};

typedef enum
{
    INPUT_LEFT = 0,
    INPUT_RIGHT,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_FOCUS,
    INPUT_HYPER,
    INPUT_FIRE,
    INPUT_MENU,
    INPUT_RESTART,

    INPUT_COUNT
} INPUTS;
struct GameInput
{
    std::string name;
    std::vector<MyKey> keys;
    std::vector<MyButton> buttons;
};
class InputHandler {
public:
    static const std::vector<MyKey> leftInputs;
    static const std::vector<MyKey> rightInputs;
    static const std::vector<MyKey> upInputs;
    static const std::vector<MyKey> downInputs;
    static const std::vector<MyKey> focusInputs;
    static const std::vector<MyKey> hyperInputs;
    static const std::vector<MyKey> fireInputs;
    static const std::vector<MyKey> menuInputs;
    static const std::vector<MyKey> restartInputs;

    static const std::vector<MyButton> leftInputsGamepad;
    static const std::vector<MyButton> rightInputsGamepad;
    static const std::vector<MyButton> upInputsGamepad;
    static const std::vector<MyButton> downInputsGamepad;
    static const std::vector<MyButton> focusInputsGamepad;
    static const std::vector<MyButton> hyperInputsGamepad;
    static const std::vector<MyButton> fireInputsGamepad;
    static const std::vector<MyButton> menuInputsGamepad;
    static const std::vector<MyButton> restartInputsGamepad;
private:
    static const std::array<std::shared_ptr<GameInput>, INPUT_COUNT> gameInputs;
    static Vector2 inputVector;

    static auto getGameInput(const INPUTS _i)
    {
        return gameInputs.at(_i);
    }

    static void UpdateInputVector()
    {
        if (CheckInputsPressed(INPUT_LEFT))
            inputVector.x = -1;
        else if (CheckInputsPressed(INPUT_RIGHT))
            inputVector.x = 1;
        else if (CheckInputsReleased(INPUT_LEFT)) {
            if (CheckInputsDown(INPUT_RIGHT))
                inputVector.x = 1;
            else
                inputVector.x = 0;
        } else if (CheckInputsReleased(INPUT_RIGHT)) {
            if (CheckInputsDown(INPUT_LEFT))
                inputVector.x = -1;
            else
                inputVector.x = 0;
        }

        if (CheckInputsPressed(INPUT_UP))
            inputVector.y = -1;
        else if (CheckInputsPressed(INPUT_DOWN))
            inputVector.y = 1;
        else if (CheckInputsReleased(INPUT_UP)) {
            if (CheckInputsDown(INPUT_DOWN))
                inputVector.y = 1;
            else
                inputVector.y = 0;
        } else if (CheckInputsReleased(INPUT_DOWN)) {
            if (CheckInputsDown(INPUT_UP))
                inputVector.y = -1;
            else
                inputVector.y = 0;
        }
    }
    public:

    static auto GetGameInputList() {
        return &gameInputs;
    }

    static std::vector<KeyboardKey> GetGameInputKeys (const INPUTS _i)
    {
        std::vector<KeyboardKey> keys;
        for (const auto& j : getGameInput(_i)->keys)
        {
            keys.emplace_back(j.k);
        }
        return keys;
    }

    static bool CheckInputsPressedMenu(const INPUTS i)
    {
        for (const auto& j : getGameInput(i)->keys)
        {
            if (j.md && !j.ml)
                return true;
        }
        for (const auto& j : getGameInput(i)->buttons)
        {
            if (j.md && !j.ml)
                return true;
        }
        return false;
    }

    static bool CheckInputsPressed(const INPUTS i) {
        for (const auto& j : getGameInput(i)->keys)
        {
            if (j.d && !j.l)
                return true;
        }
        for (const auto& j : getGameInput(i)->buttons)
        {
            if (j.d && !j.l)
                return true;
        }
        return false;
    }

    static bool CheckInputsDown(const INPUTS i) {
        for (const auto& j : getGameInput(i)->keys)
        {
            if (j.d)
                return true;
        }
        for (const auto& j : getGameInput(i)->buttons)
        {
            if (j.d)
                return true;
        }
        return false;
    }
    static bool CheckInputsDown(int i) {
        for (const auto& j : getGameInput(static_cast<INPUTS>(i))->keys)
        {
            if (j.d)
                return true;
        }
        for (const auto& j : getGameInput(static_cast<INPUTS>(i))->buttons)
        {
            if (j.d)
                return true;
        }
        return false;
    }

    static bool CheckInputsReleased(const INPUTS i) {
        for (const auto& j : getGameInput(i)->keys)
        {
            if (!j.d && j.l)
                return true;
        }
        for (const auto& j : getGameInput(i)->buttons)
        {
            if (!j.d && j.l)
                return true;
        }
        return false;
    }

    static void UpdateInputsMenu()
    {
        for (int j = 0; j < INPUT_COUNT; j++)
        {
            for (auto& k: gameInputs.at(j)->keys)
            {
                k.ml = k.md;
                k.md = IsKeyDown(k.k);
            }

            for (auto& k: gameInputs.at(j)->buttons)
            {
                k.ml = k.md;
                k.md = false;
                int i = -1;
                while (IsGamepadAvailable(++i))
                {
                    if (IsGamepadButtonDown(i, k.b))
                    {
                        k.md = true;
                        break;
                    }
                }
            }
        }
    }

    static void ClearInputsMenu()
    {
        for (int j = 0; j < INPUT_COUNT; j++)
        {
            for (auto& k: gameInputs.at(j)->keys)
            {
                k.md = true;
                k.ml = true;
            }
            for (auto& k: gameInputs.at(j)->buttons)
            {
                k.md = true;
                k.ml = true;
            }
        }
    }

    static void UpdateInputs()
    {
        for (int j = 0; j < INPUT_COUNT; j++)
        {
            for (auto& k: gameInputs.at(j)->keys)
            {
                k.l = k.d;
                k.d = IsKeyDown(k.k);
            }

            for (auto& k: gameInputs.at(j)->buttons)
            {
                k.l = k.d;
                k.d = false;
                int i = -1;
                while (IsGamepadAvailable(++i))
                {
                    if (IsGamepadButtonDown(i, k.b))
                    {
                        k.d = true;
                        break;
                    }
                }
            }
        }
        UpdateInputVector();
    }

    static Vector2 GetInputVector()
    {
        return inputVector;
    }


    static void SetKeyBind(const std::shared_ptr<GameInput>& i, const size_t index, const KeyboardKey _newBind)
    {
        i->keys.at(index).k = _newBind;
    }

    static void SetButtonBind(const std::shared_ptr<GameInput>& i, const size_t index, GamepadButton _newBind)
    {
        i->buttons.at(index).b = _newBind;
    }
};


#endif //RAYLIB_STG_INPUTHANDLER_H
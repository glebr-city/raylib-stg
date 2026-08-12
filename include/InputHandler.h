//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

#include "raylib/raylib.h"

struct MyKey
{
    KeyboardKey k = KEY_SPACE; //Keys (as on a keyboard).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
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
    INPUT_RESTART,

    INPUT_COUNT
} INPUTS;
class InputHandler {

public:
    static const std::vector<MyKey> leftInputs;
    static const std::vector<MyKey> rightInputs;
    static const std::vector<MyKey> upInputs;
    static const std::vector<MyKey> downInputs;
    static const std::vector<MyKey> focusInputs;
    static const std::vector<MyKey> hyperInputs;
    static const std::vector<MyKey> fireInputs;
    static const std::vector<MyKey> restartInputs;
private:
    static const std::array<std::shared_ptr<std::vector<MyKey>>, INPUT_COUNT> gameInputs;

    static Vector2 inputVector;
    static auto getGameInput(const INPUTS _i)
    {
        return gameInputs.at(static_cast<int>(_i));
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


    static bool CheckInputsPressed(const INPUTS i) {
        for (const auto& j : *getGameInput(i))
        {
            if (j.d && !j.l)
                return true;
        }
        return false;
    }

    static bool CheckInputsDown(const INPUTS i) {
        for (const auto& j : *getGameInput(i))
        {
            if (j.d)
                return true;
        }
        return false;
    }
    static bool CheckInputsDown(int i) {
        for (const auto& j : *getGameInput(static_cast<INPUTS>(i)))
        {
            if (j.d)
                return true;
        }
        return false;
    }

    static bool CheckInputsReleased(const INPUTS i) {
        for (const auto& j : *getGameInput(i))
        {
            if (!j.d && j.l)
                return true;
        }
        return false;
        /*if (std::ranges::any_of(getGameInput(static_cast<INPUTS>(i))->k, [](const KeyboardKey key) {return IsKeyReleased(key);}))
            return true;
        return false;*/
        //return (getGameInput(i)->l && !getGameInput(i)->d);
    }

    static void UpdateInputs()
    {
        for (int j = 0; j < INPUT_COUNT; j++)
        {
            for (auto& [k, d, l] : *gameInputs.at(j))
            {
                l = d;
                d = IsKeyDown(k);
                std::cout << d << std::endl;
            }
        }
        UpdateInputVector();
    }

    static Vector2 GetInputVector()
    {
        return inputVector;
    }
};


#endif //RAYLIB_STG_INPUTHANDLER_H
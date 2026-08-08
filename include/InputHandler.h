//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <array>
#include <iostream>

#include "raylib/raylib.h"

static inline constexpr std::array<KeyboardKey, 3> leftKeys = {KEY_P, KEY_LEFT, KEY_A};
static inline constexpr std::array<KeyboardKey, 3> rightKeys = {KEY_RIGHT, KEY_RIGHT_BRACKET, KEY_D};
static inline constexpr std::array<KeyboardKey, 3> upKeys = {KEY_UP, KEY_RIGHT_ALT, KEY_W};
static inline constexpr std::array<KeyboardKey, 3> downKeys = {KEY_DOWN, KEY_LEFT_BRACKET, KEY_S};
static inline constexpr std::array<KeyboardKey, 3> focusKeys = {KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_SPACE};
static inline constexpr std::array<KeyboardKey, 3> hyperKeys = {KEY_X, KEY_LEFT_CONTROL, KEY_PERIOD};
static inline constexpr std::array<KeyboardKey, 2> fireKeys = {KEY_Z, KEY_SLASH};
class InputHandler {
private: static Vector2 inputVector;
    public:
    static bool CheckInputsPressed(const std::array<KeyboardKey, 3> &keyArray);
    static bool CheckInputsPressed(const std::array<KeyboardKey, 2> &keyArray);
    static bool CheckInputsDown(const std::array<KeyboardKey, 3> &keyArray);
    static bool CheckInputsDown(const std::array<KeyboardKey, 2> &keyArray);
    static bool CheckInputsReleased(const std::array<KeyboardKey, 3> &keyArray);
    static bool CheckInputsReleased(const std::array<KeyboardKey, 2> &keyArray);

    static void UpdateInputVector()
    {
        if (InputHandler::CheckInputsPressed(leftKeys))
            inputVector.x = -1;
        else if (InputHandler::CheckInputsPressed(rightKeys))
            inputVector.x = 1;
        else if (InputHandler::CheckInputsReleased(leftKeys)) {
            if (InputHandler::CheckInputsDown(rightKeys))
                inputVector.x = 1;
            else
                inputVector.x = 0;
        } else if (InputHandler::CheckInputsReleased(rightKeys)) {
            if (InputHandler::CheckInputsDown(leftKeys))
                inputVector.x = -1;
            else
                inputVector.x = 0;
        }

        if (InputHandler::CheckInputsPressed(upKeys))
            inputVector.y = -1;
        else if (InputHandler::CheckInputsPressed(downKeys))
            inputVector.y = 1;
        else if (InputHandler::CheckInputsReleased(upKeys)) {
            if (InputHandler::CheckInputsDown(downKeys))
                inputVector.y = 1;
            else
                inputVector.y = 0;
        } else if (InputHandler::CheckInputsReleased(downKeys)) {
            if (InputHandler::CheckInputsDown(upKeys))
                inputVector.y = -1;
            else
                inputVector.y = 0;
        }
    }
    static Vector2 GetInputVector()
    {
        return inputVector;
    }
};


#endif //RAYLIB_STG_INPUTHANDLER_H
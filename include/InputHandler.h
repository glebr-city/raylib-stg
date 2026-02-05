//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <array>

#include "raylib.h"


class InputHandler {
    public:
    static bool CheckInputsPressed(const std::array<KeyboardKey, 3> &keyArray);
    static bool CheckInputsDown(const std::array<KeyboardKey, 3> &keyArray);
    static bool CheckInputsReleased(const std::array<KeyboardKey, 3> &keyArray);
};


#endif //RAYLIB_STG_INPUTHANDLER_H
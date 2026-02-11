//
// Created by g on 05/02/2026.
//

#include "../include/InputHandler.h"

#include <algorithm>

bool InputHandler::CheckInputsPressed(const std::array<KeyboardKey, 3> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyPressed(key);}))
        return true;
    return false;
}
bool InputHandler::CheckInputsPressed(const std::array<KeyboardKey, 2> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyPressed(key);}))
        return true;
    return false;
}

bool InputHandler::CheckInputsDown(const std::array<KeyboardKey, 3> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyDown(key);}))
        return true;
    return false;
}
bool InputHandler::CheckInputsDown(const std::array<KeyboardKey, 2> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyDown(key);}))
        return true;
    return false;
}

bool InputHandler::CheckInputsReleased(const std::array<KeyboardKey, 3> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyReleased(key);}))
        return true;
    return false;
}
bool InputHandler::CheckInputsReleased(const std::array<KeyboardKey, 2> &keyArray) {
    if (std::any_of(keyArray.begin(), keyArray.end(), [](KeyboardKey key) {return IsKeyReleased(key);}))
        return true;
    return false;
}

//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <memory>
#include <vector>

#include "OtherInputHandlers.h"
#include "raylib/raylib.h"



class InputHandler {
private:
    static IInputHandler* currentInputHandler;
public:
    static void Init() {
        currentInputHandler = new ReplayInputHandler();
        //GlobalVariables::SetCurrentReplayInputs(64);
    }
    static auto GetGameInputList() {
        return IInputHandler::GetGameInputList();
    }

    static std::vector<KeyboardKey> GetGameInputKeys (const INPUTS _i)
    {
        return IInputHandler::GetGameInputKeys(_i);
    }

    static bool CheckInputsPressedMenu(const INPUTS i)
    {
        return currentInputHandler->CheckInputsPressedMenu(i);
    }

    static bool CheckInputsPressed(const INPUTS i) {
        return currentInputHandler->CheckInputsPressed(i);
    }

    static bool CheckInputsDown(const INPUTS i) {
        return currentInputHandler->CheckInputsDown(i);
    }
    static bool CheckInputsDown(int i) {
        return currentInputHandler->CheckInputsDown(i);
    }

    static bool CheckInputsReleased(const INPUTS i) {
        return currentInputHandler->CheckInputsReleased(i);
    }

    static void UpdateInputsMenu()
    {
        return currentInputHandler->UpdateInputsMenu();
    }

    static void ClearInputsMenu()
    {
        return currentInputHandler->ClearInputsMenu();
    }

    static void UpdateInputs()
    {
        return currentInputHandler->UpdateInputs();
    }

    static Vector2 GetInputVector()
    {
        return IInputHandler::GetInputVector();
    }


    static void SetKeyBind(const std::shared_ptr<GameInput>& i, const size_t index, const KeyboardKey _newBind)
    {
        return IInputHandler::SetKeyBind(i, index, _newBind);
    }

    static void SetButtonBind(const std::shared_ptr<GameInput>& i, const size_t index, GamepadButton _newBind)
    {
        return IInputHandler::SetButtonBind(i, index, _newBind);
    }
};
#endif //RAYLIB_STG_INPUTHANDLER_H
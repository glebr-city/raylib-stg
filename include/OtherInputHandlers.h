//
// Created by g on 30/10/2026.
//

#ifndef RAYLIB_STG_OTHERINPUTHANDLERS_H
#define RAYLIB_STG_OTHERINPUTHANDLERS_H
#include <array>
#include <memory>

#include "IInputHandler.h"
#include "raylib.h"

class DefaultInputHandler : public IInputHandler {
public:

protected:
    void UpdateInputVector() override
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

    bool CheckInputsPressedMenu(const INPUTS i) override
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

    bool CheckInputsPressed(const INPUTS i) override {
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

    bool CheckInputsDown(const INPUTS i) override {
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
    bool CheckInputsDown(int i) override {
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

    bool CheckInputsReleased(const INPUTS i) override {
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

    void UpdateInputsMenu() override
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

    void ClearInputsMenu() override
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

    void UpdateInputs() override
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
};

class ReplayInputHandler : public IInputHandler {
public:

protected:
    void UpdateInputVector() override
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

    bool CheckInputsPressedMenu(const INPUTS i) override
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

    bool CheckInputsPressed(const INPUTS i) override {
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

    bool CheckInputsDown(const INPUTS i) override {
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
    bool CheckInputsDown(int i) override {
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

    bool CheckInputsReleased(const INPUTS i) override {
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

    void UpdateInputsMenu() override
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

    void ClearInputsMenu() override
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

    void UpdateInputs() override
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
};
#endif //RAYLIB_STG_OTHERINPUTHANDLERS_H
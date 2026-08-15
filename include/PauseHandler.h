//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_PAUSEHANDLER_H
#define RAYLIB_STG_PAUSEHANDLER_H
#include "ConfigHandler.h"
#include "InputHandler.h"
#include "SoundHandler.h"

class PauseHandler
{
private:
    static bool isPaused;
    static bool buttonReleased;
    public:

    static void SetPause(const bool _p)
    {
        InputHandler::ClearInputsMenu();
        if (!isPaused && _p)
        {
            buttonReleased = false;
        }
        else
        {
            ConfigHandler::WriteFile();
        }
        isPaused = _p;
        SoundHandler::SetAllSoundPause(_p);
    }

    static void TogglePause()
    {
        SetPause(!isPaused);
    }

    static bool GetPaused()
    {
        return isPaused;
    }

    static bool GetReleased()
    {
        return buttonReleased;
    }
    static void ReleaseButton()
    {
        buttonReleased = true;
    }
};

#endif //RAYLIB_STG_PAUSEHANDLER_H
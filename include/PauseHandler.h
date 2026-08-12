//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_PAUSEHANDLER_H
#define RAYLIB_STG_PAUSEHANDLER_H

class PauseHandler
{
private:
    static bool isPaused;
    public:

    static void SetPause(const bool _p)
    {
        isPaused = _p;
    }

    static void TogglePause()
    {
        isPaused = !isPaused;
    }

    static bool GetPaused()
    {
        return isPaused;
    }
};

#endif //RAYLIB_STG_PAUSEHANDLER_H
//
// Created by n on 03/09/2026.
//

#ifndef RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
#define RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
#include <cstddef>

typedef enum
{
    DEFAULT_MAIN_LOOP = 0,
    PAUSED_MAIN_LOOP,
    TITLE_CARD_MAIN_LOOP,
    CONTINUE_PROMPT_MAIN_LOOP,
    DEAD_PLAYER_MAIN_LOOP,
    MAIN_LOOP_COUNT
}MAIN_LOOPS;

class IMainLoop;

class CurrentMainLoopHolder
{
    static MAIN_LOOPS currentMainLoop;

    static MAIN_LOOPS previousMainLoop;
    public:
    static void SetMainLoop(const MAIN_LOOPS newLoop)
    {
        previousMainLoop = currentMainLoop;
        currentMainLoop = newLoop;
    }
    static void SetMainLoop(const size_t newLoop)
    {
        currentMainLoop = static_cast<MAIN_LOOPS>(newLoop);
    }
    static size_t GetCurrentMainLoopIndex()
    {
        return static_cast<size_t>(currentMainLoop);
    }

    static size_t GetPreviousMainLoopIndex()
    {
        return static_cast<size_t>(previousMainLoop);
    }
};
#endif //RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
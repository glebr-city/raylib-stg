//
// Created by n on 03/09/2026.
//

#ifndef RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
#define RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
#include <cstddef>

#include "MainLoop.h"

typedef enum
{
    DEFAULT_MAIN_LOOP = 0,
    PAUSED_MAIN_LOOP,
    TITLE_CARD_MAIN_LOOP,
    MAIN_LOOP_COUNT
}MAIN_LOOPS;

class IMainLoop;

class CurrentMainLoopHolder
{
    static MAIN_LOOPS currentMainLoop;
    public:
    static void SetMainLoop(const MAIN_LOOPS newLoop)
    {
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
};
#endif //RAYLIB_STG_CURRENTMAINLOOPHOLDER_H
//
// Created by n on 03/09/2026.
//

#ifndef RAYLIB_STG_MAINLOOPHANDLER_H
#define RAYLIB_STG_MAINLOOPHANDLER_H
#include "CurrentMainLoopHolder.h"
#include "MainLoop.h"
#include "OtherMainLoops.h"


class MainLoopHandler
{
    static constexpr auto defaultMainLoop = DefaultMainLoop();
    static constexpr auto pausedMainLoop = PausedMainLoop();
    static constexpr auto titleCardMainLoop = TitleCardMainLoop();
    static constexpr auto continuePromptMainLoop = ContinuePromptMainLoop();
    static constexpr auto deadPlayerMainLoop = DeadPlayerMainLoop();
    static const IMainLoop* mainLoops[MAIN_LOOP_COUNT];

public:
    static void InitApplication()
    {
        MoreCompleteMainLoop::InitApplication();

    }
    static void DoMainLoop()
    {
       mainLoops[CurrentMainLoopHolder::GetCurrentMainLoopIndex()]->DoMainLoop();
    }
};
#endif //RAYLIB_STG_MAINLOOPHANDLER_H
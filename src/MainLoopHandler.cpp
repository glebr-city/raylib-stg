#include "MainLoopHandler.h"
//
// Created by n on 03/09/2026.
//
MAIN_LOOPS CurrentMainLoopHolder::currentMainLoop = DEFAULT_MAIN_LOOP;
MAIN_LOOPS CurrentMainLoopHolder::previousMainLoop = DEFAULT_MAIN_LOOP;
int* IMainLoop::zoomFactor = nullptr;
RenderTexture2D* IMainLoop::target = GlobalVariables::GetRenderTexture();
const IMainLoop* MainLoopHandler::mainLoops[MAIN_LOOP_COUNT] {
    (&defaultMainLoop),
    (&pausedMainLoop),
    (&titleCardMainLoop),
    (&continuePromptMainLoop),
    (&deadPlayerMainLoop),
};
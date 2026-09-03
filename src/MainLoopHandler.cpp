#include "MainLoopHandler.h"
//
// Created by n on 03/09/2026.
//
MAIN_LOOPS CurrentMainLoopHolder::currentMainLoop = DEFAULT_MAIN_LOOP;
int* IMainLoop::zoomFactor = nullptr;
RenderTexture2D* IMainLoop::target = GlobalVariables::GetRenderTexture();
const IMainLoop* MainLoopHandler::mainLoops[MAIN_LOOP_COUNT] {
    static_cast<const IMainLoop*>(&defaultMainLoop),
    static_cast<const IMainLoop*>(&pausedMainLoop),
    static_cast<const IMainLoop*>(&titleCardMainLoop),
};
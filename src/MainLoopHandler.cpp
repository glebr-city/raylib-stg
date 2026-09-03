#include "MainLoopHandler.h"
//
// Created by n on 03/09/2026.
//
const DefaultMainLoop MainLoopHandler::defaultMainLoop = {};
const IMainLoop* MainLoopHandler::currentMainLoop = {&MainLoopHandler::defaultMainLoop};
int* IMainLoop::zoomFactor = nullptr;
RenderTexture2D* IMainLoop::target = GlobalVariables::GetRenderTexture();
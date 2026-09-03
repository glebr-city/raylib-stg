//
// Created by n on 03/09/2026.
//

#ifndef RAYLIB_STG_MAINLOOP_H
#define RAYLIB_STG_MAINLOOP_H
#include "raylib.h"

class IMainLoop
{
protected:
    static int* zoomFactor;
    static RenderTexture2D* target;
public:


public:
    virtual ~IMainLoop() = default;
    virtual void DoMainLoop() const = 0;
};
#endif //RAYLIB_STG_MAINLOOP_H
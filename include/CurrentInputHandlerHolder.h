//
// Created by g on 30/10/2026.
//

#ifndef RAYLIB_STG_CURRENTINPUTHANDLERHOLDER_H
#define RAYLIB_STG_CURRENTINPUTHANDLERHOLDER_H
#include <cstddef>
typedef enum
{
    DEFAULT_INPUT_HANDLER = 0,
    REPLAY_INPUT_HANDLER,

    INPUT_HANDLER_COUNT
}INPUT_HANDLERS;

class CurrentInputHandlerHolder
{
    static INPUT_HANDLERS currentInputHandler;

public:
    static void SetMainLoop(const INPUT_HANDLERS newHandler)
    {
        currentInputHandler = newHandler;
    }
    static void SetInputHandler(const size_t newHandler)
    {
        currentInputHandler = static_cast<INPUT_HANDLERS>(newHandler);
    }
    static size_t GetCurrentInputHandlerIndex()
    {
        return static_cast<size_t>(currentInputHandler);
    }

};
#endif //RAYLIB_STG_CURRENTINPUTHANDLERHOLDER_H
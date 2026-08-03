//
// Created by n on 02/08/2026.
//

#ifndef RAYLIB_STG_SOUNDHANDLER_H
#define RAYLIB_STG_SOUNDHANDLER_H
#include <array>
#include <cstdint>

#include "raylib.h"

typedef enum
{
    THUMP_1 = 0,
    HUM_1 = 1,
    SLIDE_1 = 2,
    SLIDE_2 = 3,
    SLIDE_3 = 4,
    SLIDE_4 = 5,
} SOUNDS;

class SoundHandler
{
private:
    public:
    static void InitSounds(); //Run at the start of the game
    static void SetAllSoundVolume(float v);
    static uint8_t PlaySound(SOUNDS i, bool loop = false, uint8_t index = 255);
    static void StopSound(SOUNDS i, uint8_t index = 255);
    static void StopAllSounds();
    static bool IsSoundPlaying(SOUNDS i, uint8_t index = 255);

};
#endif //RAYLIB_STG_SOUNDHANDLER_H
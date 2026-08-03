//
// Created by n on 02/08/2026.
//

#ifndef RAYLIB_STG_SOUNDHANDLER_H
#define RAYLIB_STG_SOUNDHANDLER_H
#include <array>
#include <cstdint>
#include <vector>

#include "raylib.h"

typedef enum
{
    THUMP_1 = 0,
    HUM_1 = 1,
    SLIDE_1 = 2,
    SLIDE_2 = 3,
    SLIDE_3 = 4,
    SLIDE_4 = 5,
    BANG_1 = 6,
    BANG_2 = 7,
    PLAYER_HIT = 8,
    PLAYER_HYPER_1 = 9,
    PLAYER_HYPER_2 = 10,
    PLAYER_HYPER_3 = 11,
    PLAYER_GRAZE_1 = 12,
    PLAYER_GRAZE_2 = 13,
} SOUNDS;

class SoundHandler
{
private:
    public:
    static void InitSounds(); //Run at the start of the game
    static void SetAllSoundVolume(float v);
    static uint8_t PlaySound(SOUNDS i, bool loop = false, uint8_t index = 255);
    static SOUNDS PlayAnySound(const std::vector<SOUNDS>& i, bool loop = false, uint8_t index = 255);
    static void StopSound(SOUNDS i, uint8_t index = 255);
    static void StopAllSounds();
    static bool IsSoundPlaying(SOUNDS i, uint8_t index = 255);

};
#endif //RAYLIB_STG_SOUNDHANDLER_H
//
// Created by n on 02/08/2026.
//

#ifndef RAYLIB_STG_SOUNDHANDLER_H
#define RAYLIB_STG_SOUNDHANDLER_H
#include <array>
#include <cstdint>
#include <vector>

#include "raylib/raylib.h"

typedef enum
{
    THUMP_1 = 0,
    HUM_1,
    SLIDE_1,
    SLIDE_2,
    SLIDE_3,
    SLIDE_4,
    BANG_1,
    BANG_2,
    PLAYER_HIT,
    PLAYER_HYPER_1,
    PLAYER_HYPER_2,
    PLAYER_HYPER_3,
    PLAYER_GRAZE_1,
    PLAYER_GRAZE_2,
    EXPLOSION_1,
    EXPLOSION_1_SHORT,
    EXPLOSION_2,

    SOUND_COUNT
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
//
// Created by n on 02/08/2026.
//

#ifndef RAYLIB_STG_SOUNDHANDLER_H
#define RAYLIB_STG_SOUNDHANDLER_H
#include <array>
#include <cstdint>
#include <vector>
#include <SoundData.h>

#include "raylib/raylib.h"

class SoundData;

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
    CLICK_1,
    MAGIC_1,
    PLAYER_RESURRECTION,

    SOUND_COUNT
} SOUNDS;

constexpr size_t SOUND_MAX_OVERLAP = 2; //How many instances of the same sound can play at a time?
class SoundHandler
{
private:
    static float soundVolume;
    static std::vector<SoundData> sounds;
    public:
    static void InitSounds() //Run at the start of the game
    {
        sounds.reserve(SOUND_COUNT);
        sounds.emplace_back("resources/sounds/thump1.mp3");
        sounds.emplace_back("resources/sounds/hum1.mp3");
        sounds.emplace_back("resources/sounds/slide1.mp3");
        sounds.emplace_back("resources/sounds/slide2.mp3");
        sounds.emplace_back("resources/sounds/slide3.mp3");
        sounds.emplace_back("resources/sounds/slide4.mp3");
        sounds.emplace_back("resources/sounds/bang1.mp3");
        sounds.emplace_back("resources/sounds/bang2.mp3");
        sounds.emplace_back("resources/sounds/playerHit.mp3");
        sounds.emplace_back("resources/sounds/playerHyper.mp3");
        sounds.emplace_back("resources/sounds/playerHyper2.mp3");
        sounds.emplace_back("resources/sounds/playerHyper3.mp3");
        sounds.emplace_back("resources/sounds/playerGraze1.mp3");
        sounds.emplace_back("resources/sounds/playerGraze2.mp3");
        sounds.emplace_back("resources/sounds/explosion1.mp3");
        sounds.emplace_back("resources/sounds/explosion1Short.mp3");
        sounds.emplace_back("resources/sounds/explosion2.mp3");
        sounds.emplace_back("resources/sounds/click1.mp3");
        sounds.emplace_back("resources/sounds/magic1.mp3");
        sounds.emplace_back("resources/sounds/playerResurrection.mp3");
    }
    static void SetAllSoundVolume(float v); //It doesn't seem to work?
    static void SetAllSoundPause(bool p);
    static size_t PlaySound(SOUNDS i, bool loop = false);
    static size_t PlaySound(size_t index, SOUNDS i, bool loop = false);
    static SOUNDS PlayAnySound(const std::vector<SOUNDS>& i, bool loop = false, uint8_t index = 255);
    static void StopSound(SOUNDS i);
    static void StopSound(SOUNDS i, size_t index);
    static void StopAllSounds();
    static bool IsSoundPlaying(SOUNDS i, size_t index);
    static bool IsSoundPlaying(SOUNDS i);

};
#endif //RAYLIB_STG_SOUNDHANDLER_H
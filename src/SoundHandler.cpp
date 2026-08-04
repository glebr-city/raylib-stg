//
// Created by n on 02/08/2026.
//
#include "SoundHandler.h"

#include <iostream>
#include <vector>

#include "GlobalVariables.h"
const uint8_t MAX_OVERLAP = 2; //How many instances of the same sound can play at a time?
std::array<Sound, SOUND_COUNT> sounds;
std::vector<std::array<Sound, MAX_OVERLAP>> currentSounds;

void SoundHandler::InitSounds()
{
    sounds = {
        LoadSound("resources/sounds/thump1.mp3"),
        LoadSound("resources/sounds/hum1.mp3"),
        LoadSound("resources/sounds/slide1.mp3"),
        LoadSound("resources/sounds/slide2.mp3"),
        LoadSound("resources/sounds/slide3.mp3"),
        LoadSound("resources/sounds/slide4.mp3"),
        LoadSound("resources/sounds/bang1.mp3"),
        LoadSound("resources/sounds/bang2.mp3"),
        LoadSound("resources/sounds/playerHit.mp3"),
        LoadSound("resources/sounds/playerHyper.mp3"),
        LoadSound("resources/sounds/playerHyper2.mp3"),
        LoadSound("resources/sounds/playerHyper3.mp3"),
        LoadSound("resources/sounds/playerGraze1.mp3"),
        LoadSound("resources/sounds/playerGraze2.mp3"),
    };
    currentSounds = {};
    for (int j = 0; j < sounds.size(); j++)
    {
        std::array<Sound, MAX_OVERLAP> newArray{};
        currentSounds.emplace_back(newArray);
        for (int k = 0; k < MAX_OVERLAP; k++)
        {
            currentSounds[j][k] = LoadSoundAlias(sounds[j]);
        }
    }

};

void SoundHandler::SetAllSoundVolume(const float v)
{
    for (uint8_t j = 0; j < MAX_OVERLAP; j++)
    {
        for (const Sound sound : currentSounds[j])
            ::SetSoundVolume(sound, v);
    }
}



uint8_t SoundHandler::PlaySound(const SOUNDS i, bool loop, const uint8_t index)
{
    if (index < MAX_OVERLAP)
    {
        if (loop && ::IsSoundPlaying(currentSounds[i][index]))
            return index;
        ::PlaySound(currentSounds[i][index]);
        return index;
    }
    std::array<uint, MAX_OVERLAP> frameCounts{};
    for (uint8_t j = 0; j < MAX_OVERLAP; j++) //See if any Sounds are free.
    {
        if (!::IsSoundPlaying(currentSounds[i][j]))
        {
            ::PlaySound(currentSounds[i][j]);
            return j;
        }
        frameCounts[j] = currentSounds[i][j].frameCount;
    }
    uint16_t largestFrameCount = 0;
    uint8_t largestIndex = 0;
    for (uint8_t _frameCount = 0; _frameCount < MAX_OVERLAP; _frameCount++) //No sounds are free; find the one farthest into its playback, and restart it.
    {
        if (frameCounts[_frameCount] > largestFrameCount)
        {
            largestFrameCount = frameCounts[_frameCount];
            largestIndex = _frameCount;
        }
    }
    ::PlaySound(currentSounds[i][largestIndex]);
    return 0;
}

SOUNDS SoundHandler::PlayAnySound(const std::vector<SOUNDS>& i, bool loop, uint8_t index)
{
    if (index < MAX_OVERLAP)
    {
        for (const SOUNDS _sound : i)
        {
            if (!IsSoundPlaying(_sound, index))
            {
                PlaySound(_sound, loop, index);
                return _sound;
            }
        }
        PlaySound(i[0], loop, index);
        return i[0];
    }
    for (const SOUNDS _sound : i)
    {
        if (!IsSoundPlaying(_sound))
        {
            PlaySound(_sound, loop);
            return _sound;
        }
    }
    PlaySound(i[0], loop);
    return i[0];

}

void SoundHandler::StopSound(const SOUNDS i, const uint8_t index)
{
    if (index < MAX_OVERLAP)
    {
        ::StopSound(currentSounds[i][index]);
        return;
    }
    for (const Sound j : currentSounds[i])
        ::StopSound(j);
}


void SoundHandler::StopAllSounds()
{
    for (const std::array<Sound, MAX_OVERLAP> sound : currentSounds) //Should this be using the SOUNDS enum, somehow?
    {
        for (const Sound j : sound)
            ::StopSound(j);
    }
}

bool SoundHandler::IsSoundPlaying(SOUNDS i, const uint8_t index)
{
    if (index < MAX_OVERLAP)
        return ::IsSoundPlaying(currentSounds[i][index]);

    for (const Sound j : currentSounds[i])
    {
        if (::IsSoundPlaying(j))
            return true;
    }
    return false;
}


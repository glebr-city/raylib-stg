//
// Created by n on 02/08/2026.
//
#include "SoundHandler.h"

#include <iostream>
#include <vector>

#include "GlobalVariables.h"
#include "SoundData.h"
float SoundHandler::soundVolume = 1;

std::vector<SoundData> SoundHandler::sounds = {};
void SoundHandler::InitSounds()
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
}

void SoundHandler::SetAllSoundVolume(const float v)
{
    return;/*
    soundVolume = v;
    for (uint8_t j = 0; j < MAX_OVERLAP; j++)
    {
        for (const Sound sound : currentSounds[j])
            ::SetSoundVolume(sound, v);
    }*/
}

void SoundHandler::SetAllSoundPause(const bool p)
{
    if (p)
    {
        for (const SoundData& sound : sounds)
            {
                sound.Pause();
            }
    } else
    {
            for (const SoundData& sound : sounds)
            {
                sound.Resume();
            }
    }
}
size_t SoundHandler::PlaySound(const SOUNDS i, const bool loop)
{
    return sounds.at(static_cast<size_t>(i)).Play(loop);
}


size_t SoundHandler::PlaySound(const size_t index, const SOUNDS i, const bool loop)
{
    return sounds.at(static_cast<size_t>(i)).Play(index, loop);
    /*
    if (index < MAX_OVERLAP)
    {
        if (loop && ::IsSoundPlaying(currentSounds[i][index]))
            return index;
        (currentSounds[i][index].);
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
    */
}

SOUNDS SoundHandler::PlayAnySound(const std::vector<SOUNDS>& i, bool loop, uint8_t index)
{
    if (index < SOUND_MAX_OVERLAP)
    {
        for (const SOUNDS _sound : i)
        {
            if (!IsSoundPlaying(_sound, index))
            {
                PlaySound(index, _sound, loop);
                return _sound;
            }
        }
        PlaySound(index, i[0], loop);
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


void SoundHandler::StopSound(const SOUNDS i)
{
    sounds.at(static_cast<size_t>(i)).StopAllSounds();
}

void SoundHandler::StopSound(const SOUNDS i, const size_t index)
{
    sounds.at(static_cast<size_t>(i)).Stop(index);
    /*if (index < MAX_OVERLAP)
    {
        ::StopSound(currentSounds[i][index]);
        return;
    }
    for (const Sound j : currentSounds[i])
        ::StopSound(j);*/
}


void SoundHandler::StopAllSounds()
{
    for (const auto& sd : sounds) //Should this be using the SOUNDS enum, somehow?
    {
        sd.StopAllSounds();
    }
}

bool SoundHandler::IsSoundPlaying(const SOUNDS i)
{
    return sounds.at(static_cast<size_t>(i)).IsPlaying();
    /*
    if (index < MAX_OVERLAP)
        return ::IsSoundPlaying(currentSounds[i][index]);

    for (const Sound j : currentSounds[i])
    {
        if (::IsSoundPlaying(j))
            return true;
    }
    return false;
    */
}

bool SoundHandler::IsSoundPlaying(const SOUNDS i, const size_t index)
{
    return sounds.at(static_cast<size_t>(i)).IsPlaying(index);
    /*
    if (index < MAX_OVERLAP)
        return ::IsSoundPlaying(currentSounds[i][index]);

    for (const Sound j : currentSounds[i])
    {
        if (::IsSoundPlaying(j))
            return true;
    }
    return false;
    */
}


//
// Created by n on 02/08/2026.
//
#include "SoundHandler.h"

#include <iostream>
#include <vector>

#include "GlobalVariables.h"
const uint8_t MAX_OVERLAP = 2; //How many instances of the same sound can play at a time?
std::array<Sound, 6> sounds;
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
    };
    currentSounds = {};
    for (int j = 0; j < sounds.size(); j++)
    {
        std::array<Sound, MAX_OVERLAP> newArray{};
        currentSounds.emplace_back(newArray);
        for (int k = 0; k < MAX_OVERLAP; k++)
        {
            currentSounds[j][k] = LoadSoundAlias(sounds[j]);
            std::cout << "Thing 0: " << IsSoundValid(currentSounds[j][k]) << std::endl;
        }
        std::cout << "Thing 1: " << IsSoundValid(currentSounds.at(0).at(0)) << std::endl;
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
    for (uint8_t j = 0; j < MAX_OVERLAP; j++)
    {
        if (!::IsSoundPlaying(currentSounds[i][j]))
        {
            ::PlaySound(currentSounds[i][j]);
            return j;
        }
    }
    ::PlaySound(currentSounds[i][0]);
    return 0;
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


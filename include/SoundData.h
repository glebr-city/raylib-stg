//
// Created by n on 12/08/2026.
//

//Code written by Jeffery Myers. Thank you! <3
#ifndef RAYLIB_STG_SOUNDDATA_H
#define RAYLIB_STG_SOUNDDATA_H
#include <stdexcept>
#include <vector>

#include "raylib.h"
#include "RNGHandler.h"

class SoundData
{
private:
    Sound MasterSound = {};
    std::vector<Sound> Instances = std::vector<Sound>();
    std::string_view DEBUG_name = {};
public:

    SoundData(const std::string_view name)
    {
        MasterSound = LoadSound(name.data());
        DEBUG_name = name;
    }

    ~SoundData()
    {
        for (const Sound& sound : Instances)
        {
            UnloadSoundAlias(sound);
        }
        UnloadSound(MasterSound);
    }

    void Pause() const
    {
        PauseSound(MasterSound);
        for (const Sound& sound : Instances)
            PauseSound(sound);
    }

    void Resume() const
    {
        ResumeSound(MasterSound);
        for (const Sound& sound : Instances)
            ResumeSound(sound);
    }


    bool IsPlaying()
    {
        if (IsSoundPlaying(MasterSound))
            return true;
        for (const auto & Instance : Instances)
        {
            if (IsSoundPlaying(Instance))
            {
                return true;
            }
        }
        return false;
    }

    bool IsPlaying(const size_t _index)
    {
        if (_index == 0)
        {
            return IsSoundPlaying(MasterSound);
        }
        if (_index >= Instances.size())
            return false;
        return IsSoundPlaying(GetSoundInstance(_index));
    }
    size_t Play(const bool loop = false)
    {
        if (!IsSoundPlaying(MasterSound))
        {
            PlaySound(MasterSound);
            SetSoundPitch(MasterSound, 0.95f + static_cast<float>(RNGHandler::GetSeed() % 2000) / 40000);
            return 0;
        }
        if (loop)
            return 0;
        for (size_t i = 0; i < Instances.size(); ++i)
        {
            if (!IsSoundPlaying(Instances[i]))
            {
                PlaySound(Instances[i]);
                return i+1;
            }
        }

        Instances.emplace_back(LoadSoundAlias(MasterSound));
        PlaySound(Instances.back());
        return Instances.size();
    }

    size_t Play(const size_t index, const bool loop = false)
    {
        if (index >= Instances.size())
            return Play();
        if (!IsPlaying(index))
            PlaySound(GetSoundInstance(index));
        return index;
    }

    Sound& GetSoundInstance(const size_t instance)
    {
        if (instance == 0)
            return MasterSound;
        else if (instance <= Instances.size())
            return Instances[instance - 1];
        else
            throw std::out_of_range("Sound instance index out of range");
    }

    void StopAllSounds() const
    {
        StopSound(MasterSound);
        for (const Sound& sound : Instances)
            StopSound(sound);
    }

    void SetVolume(const float volume, const size_t instance)
    {
        SetSoundVolume(GetSoundInstance(instance), volume);
    }

    void Stop(const size_t index)
    {
        if (index < Instances.size())
        {
            StopSound(GetSoundInstance(index));
        }
    }
};
#endif //RAYLIB_STG_SOUNDDATA_H
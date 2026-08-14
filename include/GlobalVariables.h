//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <cstdint>
#include <memory>

#include "PhaseHelper.h"

//#include "PhaseHelper.h"

class PhaseHelper;
struct PhaseRef;
inline int currentGrazeMetre = 0;
inline const int gameWidth = 120;
inline const int gameHeight = 180;
inline const int bulletSealRadius = 22; //Grounded enemies may not fire from this distance to the player.
inline const int bulletSealRadiusSQ = bulletSealRadius * bulletSealRadius; //Grounded enemies may not fire from this distance to the player.

typedef enum {
    DIAGONAL_TANKS = 0,
    PHASE_2,
    BOSS_1_PHASE_1,
    BOSS_1_PHASE_2,
    BOSS_1_PHASE_3,
    BOSS_1_PHASE_4,
    BOSS_1_PHASE_5,

    PHASE_COUNT
} PHASES;

class GlobalVariables {
protected:
    static std::unique_ptr<PhaseHelper> currentPhase;
    static const std::array<PhaseRef, PHASE_COUNT> phases;
    static RenderTexture2D renderTexture;
    static int renderTextureFilter;
    static int effectVolume;
public:

    //static std::array<PhaseRef, 2> getPhaseList(){return {};};


    static PhaseRef getPhase(const PHASES _index);

    static std::uint_fast32_t& currentStep();

    static void setCurrentPhase(const PHASES _desiredPhase);

    static PhaseHelper *getCurrentPhase() {
        return currentPhase.get();
    }

    static void DestroyCurrentPhase()
    {
        delete currentPhase.get();
        currentPhase.release();
    }

    static int getGrazeMetre() {
        return currentGrazeMetre;
    }

    static void setGrazeMetre(int i) {
        currentGrazeMetre = i;
    }

    static RenderTexture2D* GetRenderTexture()
    {
        return &renderTexture;
    }

    static int GetTextureFilter()
    {
        return renderTextureFilter;
    }

    static void SetRenderTextureFilter(const int _filter)
    {
        if (_filter == 1)
        {
            renderTextureFilter = 1;
            SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_BILINEAR);
        }
        else
        {
            renderTextureFilter = 0;
            SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_POINT);
        }
    }

    static void InitRenderTexture(const int _width, const int _height)
    {
        SetTextureWrap(renderTexture.texture, TEXTURE_WRAP_MIRROR_CLAMP);
        renderTexture = LoadRenderTexture(_width, _height);
    }

    static void SetEffectVolume(const int _volume)
    {
        effectVolume = _volume;
        SetMasterVolume(std::clamp(static_cast<float>(effectVolume) / 100, 0.0f, 1.0f));
    }

    static int GetEffectVolume()
    {
        return effectVolume;
    }
};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
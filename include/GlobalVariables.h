//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <cstdint>
#include <memory>

#include "PhaseHelper.h"
#include "Stage.h"

class PhaseHelper;
struct PhaseRef;
inline int currentGrazeMetre = 0;
inline const int gameWidth = 120;
inline const int gameHeight = 180;
inline const int bulletSealRadius = 22; //Grounded enemies may not fire from this distance to the player.
inline const int bulletSealRadiusSQ = bulletSealRadius * bulletSealRadius; //Grounded enemies may not fire from this distance to the player.






class GlobalVariables {
protected:
    static std::unique_ptr<PhaseHelper> currentPhase;
    static const std::array<PhaseRef, PHASE_COUNT> phases;
    static const std::array<std::shared_ptr<Stage>, 2> stages;
    static int currentStageIndex;
    static int currentPhaseIndex; //Within the current stage!
    static RenderTexture2D renderTexture;
    static int renderTextureFilter;
    static int effectVolume;
    static int screenRotation;
    static int zoomFactor;

    static void setCurrentPhase(const PHASES _desiredPhase)
    {
        PhaseHelper* newPhase = GetPhase(_desiredPhase).initPhase();
        currentPhase = std::unique_ptr<PhaseHelper>(newPhase);
    }
public:

    //static std::array<PhaseRef, 2> getPhaseList(){return {};};


    static PhaseRef GetPhase(const PHASES _index);


    static void SetCurrentPhase(const uint8_t _desiredPhaseIndex)
    {
        currentPhaseIndex = _desiredPhaseIndex;
        setCurrentPhase(stages.at(currentStageIndex)->GetPhase(_desiredPhaseIndex));
    }

    static std::uint_fast32_t& currentStep();

    static void NextPhase()
    {
        currentPhaseIndex++;
        setCurrentPhase(stages.at(currentStageIndex)->GetPhase(currentPhaseIndex));
    }

    static PhaseHelper *GetCurrentPhase() {
        return currentPhase.get();
    }

    static int GetCurrentPhaseIndex()
    {
        return currentPhaseIndex;
    }

    static void DestroyCurrentPhase()
    {
        delete currentPhase.get();
        currentPhase.release();
    }

    static void SetCurrentStage(const int _desiredStageIndex)
    {
        currentStageIndex = _desiredStageIndex;
    }

    static void NextStage() //Increments current stage and switches to its first phase.
    {
        currentStageIndex++;
        currentPhaseIndex = 0;
        DestroyCurrentPhase();
        setCurrentPhase(stages.at(currentStageIndex)->GetPhase(0));
    }

    static int GetCurrentStageIndex()
    {
        return currentStageIndex;
    }

    static std::shared_ptr<Stage> GetCurrentStage() {
        return stages.at(currentStageIndex);
    }

    static int GetGrazeMetre() {
        return currentGrazeMetre;
    }

    static void SetGrazeMetre(int i) {
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

    static int GetScreenRotation()
    {
        return screenRotation;
    }

    static void SetScreenRotation(const int _screenRotation)
    {
        if (_screenRotation < 0)
            screenRotation = 3;
        else if (_screenRotation > 3)
            screenRotation = 0;
        else
        screenRotation = _screenRotation;
        AdjustLetterbox();
    }

    static std::array<int, 3> AdjustLetterbox() {
        zoomFactor = 1;
        Vector2 letterboxSize = {0, 0};
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
        int screenRotation = GetScreenRotation();
        if (screenRotation == 1 || screenRotation == 3)
            aspectRatio = 1.0f / aspectRatio;
        if (aspectRatio < 1.5f) {
            if (screenRotation == 0 || screenRotation == 2)
                zoomFactor = std::fmaxf(2.0f, floor(screenHeight / gameHeight / 2) * 2);
            else
                zoomFactor = std::fmaxf(2.0f, floor(screenWidth / gameHeight / 2) * 2);
        } else {
            if (screenRotation == 0 || screenRotation == 2)
                zoomFactor = std::fmaxf(2.0f, floor(screenWidth / gameWidth / 2) * 2);
            else
                zoomFactor = std::fmaxf(2.0f, floor(screenHeight / gameWidth / 2) * 2);
        }
        //ppzoomFactor = std::max(static_cast<uint> (1), std::bit_floor(zoomFactor));
        //zoomFactor = even
        letterboxSize.x = ((screenWidth) - (gameWidth * zoomFactor)) / 2;
        letterboxSize.y = ((screenHeight) - (gameHeight * zoomFactor)) / 2;
        const int x = round(letterboxSize.x);
        const int y = round(letterboxSize.y);
        return {static_cast<int>(zoomFactor), x, y};
    }

    static int* GetZoomFactor()
    {
        return &zoomFactor;
    }
};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
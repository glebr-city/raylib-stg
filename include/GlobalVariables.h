//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <cstdint>
#include <memory>
#include "PhaseHelper.h"
#include <raylib.h>

#include "SoundHandler.h"
#include "SpriteHandlerEnums.h"
inline int currentGrazeMetre = 0;
inline const int gameWidth = 120;
inline const int gameHeight = 180;

typedef enum {
    DIAGONAL_TANKS = 0,
    TEST_PHASE_1,

    PHASE_COUNT
} PHASES;

class PhaseHelper;
class GlobalVariables {
protected:
    static std::unique_ptr<PhaseHelper> currentPhase;
    static const std::array<PhaseRef, 2> phases;
public:

    //static std::array<PhaseRef, 2> getPhaseList(){return {};};

    static PhaseRef getPhase(const PHASES _index);


    static std::uint32_t& currentStep();

    static void setCurrentPhase(const PHASES _desiredPhase);

    static PhaseHelper *getCurrentPhase() {
        return currentPhase.get();
    }

    static int getGrazeMetre() {
        return currentGrazeMetre;
    }

    static void setGrazeMetre(int i) {
        currentGrazeMetre = i;
    }



};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <memory>
#include "PhaseHelper.h"
inline int currentGrazeMetre = 0;
inline const int gameWidth = 120;
inline const int gameHeight = 180;


class PhaseHelper;
class GlobalVariables {
protected:
    static std::unique_ptr<PhaseHelper> currentPhase;
public:

    static int& currentStep();

    static void setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase);

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
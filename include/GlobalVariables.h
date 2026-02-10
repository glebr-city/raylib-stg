//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <memory>
#include <utility>

#include "PhaseHelper.h"


class PhaseHelper;

class GlobalVariables {
    private:
public:

    static std::unique_ptr<PhaseHelper> currentPhase;
    static int& currentStep();

    static int& gameHeight();

    static int& gameWidth();

    static const int& grazeRadius();

    static void setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase);

    static PhaseHelper *getCurrentPhase();
};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
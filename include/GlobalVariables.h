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
    static PoolingVector<PlayerBullet> playerBullets;

    static int& currentStep();

    static int& gameHeight();

    static int& gameWidth();

    static const int& grazeRadius();

    static void setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase);

    static PhaseHelper *getCurrentPhase();

    static void addPlayerBullet();
};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
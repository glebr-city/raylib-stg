//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_GLOBALVARIABLES_H
#define RAYLIB_STG_GLOBALVARIABLES_H
#include <memory>
#include <utility>

#include "DamageHandler.h"
#include "PhaseHelper.h"
#include "raylib.h"
#include "PoolingVector.h"
#include "PlayerBullet.h"


class PhaseHelper;

class GlobalVariables {
protected:
    static std::unique_ptr<PhaseHelper> currentPhase;
    static std::unique_ptr<PoolingVector<PlayerBullet>> playerBullets;
public:

    static int& currentStep();

    static int& gameHeight();

    static int& gameWidth();

    static const int& grazeRadius();

    static void setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase);

    static PhaseHelper *getCurrentPhase() {
        return currentPhase.get();
    }

    static void spawnPlayerBullet(Vector2 pos);

    static PoolingVector<PlayerBullet>* getPlayerBullets() {
        return playerBullets.get();
    }

    static void setCurrentGrazeMetre(int i) {
        currentGrazeMetre = i;
    }
};

#endif //RAYLIB_STG_GLOBALVARIABLES_H
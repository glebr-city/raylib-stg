//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE1_H
#define RAYLIB_STG_STAGE3PHASE1_H
#include "PhaseHelper.h"

class Stage3Phase1 : public PhaseHelper
{
    public:
    Stage3Phase1() : PhaseHelper("Stage3Phase1", {}, {0, -0.2f}, STAGE_3_BACKGROUND)
    {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);
    }
    void InitPhase() override
    {
        PlayerHandler::GetPlayer()->reset();
    };
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE1_H
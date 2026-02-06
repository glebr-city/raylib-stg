//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_PLAYER_H
#define RAYLIB_STG_PLAYER_H
#include <StepThinker.h>

#include "raylib.h"


class Player : public StepThinker{
    public:
    explicit Player(Vector2 pos);

    void PreStep() override;
    Vector2 getPosition();
};



#endif //RAYLIB_STG_PLAYER_H
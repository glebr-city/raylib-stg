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

    void doPreStep() override;

    void doPhysics(Vector2 pos);
    void doPhysics();

    Vector2 getPosition();
    Vector2 getMovement();
    std::array<Vector2, 2> getPosAndMovement();
};



#endif //RAYLIB_STG_PLAYER_H
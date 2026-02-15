//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_PLAYER_H
#define RAYLIB_STG_PLAYER_H
#include <StepThinker.h>

#include "raylib.h"


class PlayerBullet;

class Player : public StepThinker{
private:
    void startHyper();
    void endHyper();

public:
    Player(Vector2 pos);

    void reset(Vector2 pos);

    void doPreStep() override;

    void doPhysics(Vector2 pos);
    bool doPhysics() override;

    Vector2 getPosition() override;
    Vector2 getMovement();
    std::array<Vector2, 2> getPosAndMovement();
    void getHit();
};



#endif //RAYLIB_STG_PLAYER_H
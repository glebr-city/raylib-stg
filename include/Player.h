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
    void setFinalPos();

public:
    Player(Vector2 pos);

    void reset(Vector2 pos);

    void doPreStep() override;

    void doPhysics(Vector2 pos);
    bool doPhysics() override;

    Vector2 GetPosition() override;
    Vector2 GetMovement();
    Vector2 GetFinalPos();
    bool GetHyperOn();
    std::array<Vector2, 2> GetPosAndMovement();
    void getHit();
};



#endif //RAYLIB_STG_PLAYER_H
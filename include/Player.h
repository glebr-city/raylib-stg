//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_PLAYER_H
#define RAYLIB_STG_PLAYER_H
#include <StepThinker.h>

#include "raylib/raylib.h"


class PlayerBullet;

class Player : public StepThinker{
private:
    static void startHyper();
    static void endHyper();
    static void setFinalPos();

public:
    Player(Vector2 pos);

    static void reset(Vector2 pos = {60, 140}, bool _resurrect=false);
    static void respawn(Vector2 pos = {60, 140});

    void doPreStep() override;

    void doPhysics(Vector2 pos);
    bool doPhysics() override;
    void doPostStep() override;

    Vector2 GetPosition() override;
    static Vector2 GetMovement();
    static Vector2 GetFinalPos();
    static bool GetHyperOn();
    static std::array<Vector2, 2> GetPosAndMovement();
    static void getHit();
    static bool GetIsDead();
};



#endif //RAYLIB_STG_PLAYER_H
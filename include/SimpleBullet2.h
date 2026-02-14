//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2_H
#define RAYLIB_STG_SIMPLEBULLET2_H
#include "Bullet.h"
#include "SimpleBullet1.h"


class SimpleBullet2 : public SimpleBullet {
public:
    using StepThinker::doPhysics;
    SimpleBullet2();

    SimpleBullet2(Vector2 pos, Vector2 dir);

    SimpleBullet2(Vector2 pos, Vector2 dir, Color col);

    void spawn(Vector2 pos, Vector2 dir);

    void spawn(Vector2 pos, Vector2 dir, Color col);

    void doPreStep() override;

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override;


private:
    static constexpr float radius = 1.15f;
    static constexpr float speed = 2.5f;
    static constexpr ANIMATED_SPRITES sprite = BULLET_SMALL_MONOCHROME;
    Vector2 direction{};
    Color color = WHITE;
protected:
    static constexpr int grazeValue = 100;

};


#endif //RAYLIB_STG_SIMPLEBULLET2_H
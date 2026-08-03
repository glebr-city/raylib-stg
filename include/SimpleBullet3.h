//
// Created by n on 30/07/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET3_H
#define RAYLIB_STG_SIMPLEBULLET3_H
#include "SimpleBullet.h"

class SimpleBullet3 : public SimpleBullet
{
private:
    static constexpr float radius = 1.5f;
    static constexpr float speed = 1.25f;
    static constexpr int grazeValue = 40;
    static constexpr ANIMATED_SPRITES sprite = SPINNING_ROD_MONOCHROME;
    Vector2 direction{};
    Color color = WHITE;

public:
    using StepThinker::doPhysics;
    SimpleBullet3(const Vector2 pos, const Vector2 dir);

    SimpleBullet3();

    SimpleBullet3(const Vector2 pos, const Vector2 dir, Color col);
    void spawn(Vector2 pos, Vector2 dir);
    void spawn(Vector2 pos, Vector2 dir, Color col);
    void doPreStep() override;
    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override;
};
#endif //RAYLIB_STG_SIMPLEBULLET3_H
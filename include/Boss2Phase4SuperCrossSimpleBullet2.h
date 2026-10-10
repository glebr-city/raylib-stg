//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE4SUPERCROSSSIMPLEBULLET2_H
#define RAYLIB_STG_BOSS2PHASE4SUPERCROSSSIMPLEBULLET2_H
#include "SimpleBullet2.h"

class Boss2Phase4SuperCrossSimpleBullet2 : public SimpleBullet2
{
protected:
    static constexpr float speed = 0.75f;
    Vector2 currentPositionOffset = Vector2Zeros;
    Vector2 offsetPosition = Vector2Zeros;
public:

    static constexpr int BULLET_DISTANCE = 7;
    static constexpr std::array<Vector2, 13> BULLET_OFFSETS {Vector2{0, 0},
        {0, BULLET_DISTANCE * 2},
{BULLET_DISTANCE * -2, BULLET_DISTANCE},{0, BULLET_DISTANCE}, {BULLET_DISTANCE * 2, BULLET_DISTANCE},
{BULLET_DISTANCE * -2, 0}, {BULLET_DISTANCE * -1, 0}, {BULLET_DISTANCE, 0}, {BULLET_DISTANCE * 2, 0},
{BULLET_DISTANCE * -2, BULLET_DISTANCE * -1}, {0, BULLET_DISTANCE * -1}, {BULLET_DISTANCE * 2, BULLET_DISTANCE * -1},
                {0, BULLET_DISTANCE * -2},
    };
    int bulletIndex = 0;
    void spawn(const Vector2 pos, const Vector2 dir, const int index = 0, const Color col = RED)
    {
        SimpleBullet2::spawn(pos, dir, col);
        currentPositionOffset = Vector2Zeros;
        bulletIndex = index;
        offsetPosition = position;
    }
    Boss2Phase4SuperCrossSimpleBullet2() = default;
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(offsetPosition, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        currentPositionOffset = Vector2MoveTowards(currentPositionOffset, BULLET_OFFSETS[bulletIndex], (Vector2DistanceSqr(currentPositionOffset, BULLET_OFFSETS[bulletIndex])) * 0.001f + 0.1f);
        offsetPosition = Vector2Add(position, currentPositionOffset);

        if (offsetPosition.x < -2 || offsetPosition.x > 122 || offsetPosition.y < -100 || offsetPosition.y > 182)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = offsetPosition, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_BOSS2PHASE4SUPERCROSSSIMPLEBULLET2_H
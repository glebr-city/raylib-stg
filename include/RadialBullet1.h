//
// Created by n on 05/11/2026.
//

#ifndef RAYLIB_STG_RADIALBULLET1_H
#define RAYLIB_STG_RADIALBULLET1_H
#include "SimpleBullet1VariableSpeed.h"

class RadialBullet1 : public SimpleBullet1VariableSpeed
{
    protected:
    float angularSpeed = 0;
    unsigned int stepsElapsed = 0;
    Vector2 pivotPosition{};
    public:
    RadialBullet1() {
        grazeValue = 60;
    }
    virtual void spawn(const float _speed, const float _angularSpeed, const Vector2 pos, const Vector2 dir, const Color col)
    {
        SimpleBullet1VariableSpeed::spawn(_speed, pos, dir, col);
        stepsElapsed = 0;
        angularSpeed = _angularSpeed;
        pivotPosition = pos;
    };
    bool doPhysics() override
    {
        stepsElapsed++;
        direction = Vector2Rotate(direction, angularSpeed);
        position = pivotPosition + direction * speed * stepsElapsed;
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), Player::GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -6 || position.x > 126 || position.y < -100 || position.y > 186)
            return false;
        return true;
    }
};
#endif //RAYLIB_STG_RADIALBULLET1_H
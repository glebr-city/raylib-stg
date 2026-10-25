//
// Created by g on 13/10/2026.
//

#ifndef RAYLIB_STG_ENEMY2_H
#define RAYLIB_STG_ENEMY2_H
#include "Enemy.h"
#include "Enemy2Base.h"
#include "Enemy2Bullet1.h"


class Enemy2 : public Enemy2Base
{
private:
protected:
    std::shared_ptr<PoolingVector<Enemy2Bullet1>> bullet1Pool;
    //static constexpr STATIC_SPRITES sprite = ENEMY_2;


    void fireShot(const bool lockAngle) override
    {
        if (!lockAngle)
        {
            shotDirection = Vector2Normalize(Vector2Subtract(targetPosition, position));
            bullet1Pool->spawn().spawn(position, shotDirection, YELLOW);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, 0.3f), ORANGE);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, -0.3f), ORANGE);
        }
        else
        {
            bullet1Pool->spawn().spawn(position, shotDirection, ORANGE);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, 0.3f), YELLOW);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, -0.3f), YELLOW);
        }
    };

public:
    Enemy2(const std::shared_ptr<PoolingVector<Enemy2Bullet1>>& _bullet1Pool,
           const std::vector<Enemy2State>& _stateVector, const uint _scoreValue = 500) : Enemy2Base(
        _stateVector, _scoreValue)
    {
        bullet1Pool = _bullet1Pool;
    }


    void spawn(const EnemySpawnParametres _params) override
    {
        Enemy::spawn(_params);
        enterNewState(0);
        health = getMaxHealth();
    }

    void spawn(const Vector2 _position, const u_int _scoreValue) override
    {
        spawn({.pos = _position});
        scoreValue = _scoreValue;
    }

    void spawn(const Vector2 _position) override
    {
        spawn({.pos = _position});
    }
};
#endif //RAYLIB_STG_ENEMY2_H

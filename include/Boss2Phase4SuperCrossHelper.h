//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE4SUPERCROSSHELPER_H
#define RAYLIB_STG_BOSS2PHASE4SUPERCROSSHELPER_H
#include "Boss2Phase4SuperCrossSimpleBullet2.h"
class Boss2Phase4SuperCrossHelper : public Enemy
{
    const std::shared_ptr<PoolingVector<Boss2Phase4SuperCrossSimpleBullet2>> bulletPool;
    Vector2 direction;
    Color color;

public:

    Boss2Phase4SuperCrossHelper(std::shared_ptr<PoolingVector<Boss2Phase4SuperCrossSimpleBullet2>> _bulletPool) : bulletPool(_bulletPool){}

    void spawn(const Vector2 pos, const Vector2 dir, const Color col)
    {
        position = pos;
        direction = dir;
        color = col;
        for (int i = 0; i < Boss2Phase4SuperCrossSimpleBullet2::BULLET_OFFSETS.size(); i++)
        {
            bulletPool->spawn().spawn(position, direction, i, color);
        }

    }

    virtual bool doPhysics() override
    {
        return false;
    }
};
#endif //RAYLIB_STG_BOSS2PHASE4SUPERCROSSHELPER_H
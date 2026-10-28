//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
#define RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
#include "AcceleratingBullet2.h"
#include "Enemy.h"
#include "SimpleBullet1.h"

class Boss3Phase3Explosive : public SimpleBullet1 {
private:
    std::shared_ptr<PoolingVector<AcceleratingBullet2>> acceleratingBullet2Pool;
protected:
    float currentSpeed = 0;
    static constexpr float speed = 2;
    static constexpr float decelerationRate = 0.05f;
    static constexpr u_int stepsToExplode = 120;
    int stepsElapsed = 0;
public:
    Boss3Phase3Explosive(
    const std::shared_ptr<PoolingVector<AcceleratingBullet2>> &_acceleratingBullet2Pool) : SimpleBullet1(), acceleratingBullet2Pool(_acceleratingBullet2Pool) {}
    void spawn(const Vector2 pos, const Vector2 dir, const Color col) override {
        SimpleBullet1::spawn(pos, dir, col);
        stepsElapsed = 0;
        currentSpeed = speed;
    }

    bool doPhysics() override {
        stepsElapsed++;
        currentSpeed = std::max(0.2f, currentSpeed - decelerationRate);
        color.r = stepsElapsed * 2;
        color.g = stepsElapsed * 2;
        color.b = 255 - stepsElapsed;
        if (stepsElapsed >= stepsToExplode) {
            Vector2 shotDirection = Vector2Rotate({0, 1}, (RNGHandler::GetSeed() % 230 - 115) * 0.0136590984939);
            for (int i = 0; i < 3; i++) {
                shotDirection = Vector2Rotate(shotDirection, 2.09439510239);
                acceleratingBullet2Pool->spawn().spawn(position, shotDirection, GREEN, 0);
            }
            return false;
        }

        position = Vector2Add(position, direction * currentSpeed);
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182) {
            return false;
        }
        return true;
    }
};
#endif //RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
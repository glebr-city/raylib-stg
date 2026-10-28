//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE3BULLET1_H
#define RAYLIB_STG_BOSS3PHASE3BULLET1_H
#include "SimpleBullet1.h"

class Boss3Phase3Bullet1 : public SimpleBullet1 {
protected:
    int stepsElapsed = 0;
    int stepToStop = 0;
    bool hasStopped = false;
    bool hasExploded = false;
    bool hasDespawned = false;
    static constexpr float speed = 2;

    public:
    void spawn(const int _stepToStop, const Vector2 pos, const Vector2 dir, const Color col) {
        hasStopped = false;
        hasExploded = false;
        hasDespawned = false;
        SimpleBullet1::spawn(pos, dir, col);
        stepsElapsed = 0;
        stepToStop = _stepToStop;
    }
    void spawn(const Vector2 pos, const Vector2 dir, const Color col) override
    {
        std::cout << "Boss3Phase3Bullet1 should not spawn like this!" << std::endl;
        throw;

    }

    void spawn(Vector2 _position) override {
        std::cout << "Boss3Phase3Bullet1 should not spawn like this!" << std::endl;
        throw;
    };
    void spawn(Vector2 _position, u_int _scoreValue) override {
        std::cout << "Boss3Phase3Bullet1 should not spawn like this!" << std::endl;
        throw;
    }

    bool doPhysics() override {
        stepsElapsed++;
        if (stepsElapsed >= stepToStop) {
            hasStopped = true;
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            hasDespawned = true;
            return false;
        }
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182) {
            hasDespawned = true;
            return false;
        }
        return true;
    }
    [[nodiscard]] bool GetHasDespawned() const {
        return hasDespawned;
    }
    [[nodiscard]] bool GetHasStopped() const {
        return hasStopped;
    }
    [[nodiscard]] Vector2 GetPosition() const {
        return position;
    }


};
#endif //RAYLIB_STG_BOSS3PHASE3BULLET1_H
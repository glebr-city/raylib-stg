//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
#define RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
#include "AcceleratingBullet2.h"
#include "Enemy.h"

class Boss3Phase3Explosive : public Enemy {
private:
    float currentSpeed = 0;
    static constexpr float speed = 2;
    static constexpr float decelerationRate = 0.05f;
    static constexpr u_int stepsToExplode = 120;
    static constexpr float radius = 3;
    bool hasBeenGrazed = false;
    Vector2 direction{};
    Vector2 startOfTickPos{};
    int stepsElapsed = 0;
    Color color{};
    const std::shared_ptr<PoolingVector<AcceleratingBullet2>> acceleratingBullet2Pool;

    void setStartOfTickPos() {
        startOfTickPos = position;
    }
public:
    void spawn(const Vector2 _position, const Vector2 _direction, const Color _col) {
        Enemy::spawn({.pos=_position});
        direction = _direction;
        stepsElapsed = 0;
        currentSpeed = speed;
        setStartOfTickPos();
        color = _col;
    }
    void spawn(const EnemySpawnParametres _params) override {
        std::cout << "Boss3Phase3Explosive should not spawn like this!" << std::endl;
        throw std::runtime_error("Boss3Phase3Explosive should not spawn like this!");
        Enemy::spawn(_params);
        stepsElapsed = 0;
        currentSpeed = speed;
        setStartOfTickPos();
        color = {10, 10, 255, 255};
    }

    bool doPhysics() override {
        if (!GlobalVariables::GetCurrentPhase()->CanSpawnBullets())
            return false;
        setStartOfTickPos();
        stepsElapsed++;
        currentSpeed = std::max(0.2f, currentSpeed - decelerationRate);
        color.r = stepsElapsed * 2;
        color.g = stepsElapsed * 2;
        color.b = 255 - stepsElapsed;
        if (stepsElapsed >= stepsToExplode) {
            Vector2 shotDirection = Vector2Rotate({0, 1}, (RNGHandler::GetSeed() % 230 - 115) * 0.0136590984939);
            for (int i = 0; i < 3; i++) {
                shotDirection = Vector2Rotate(shotDirection, 2.09439510239);
                acceleratingBullet2Pool->spawn().spawn(Vector2Add(position, shotDirection * 2), shotDirection, GREEN, 0);
            }
            return false;
        }
        position = Vector2Add(position, direction * currentSpeed);
        if (Bullet::CheckCollisionRoundBullet(position, startOfTickPos, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos())) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182) {
            return false;
        }
        return true;
    }

    Boss3Phase3Explosive(const std::shared_ptr<PoolingVector<AcceleratingBullet2>>& _acceleratingBullet2Pool) :
    acceleratingBullet2Pool(_acceleratingBullet2Pool) {}

    void doPostStep() override
    {
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos= position, .l = LAYER_BULLET_HIGH, .col = color});
    }
};
#endif //RAYLIB_STG_BOSS3PHASE3EXPLOSIVE_H
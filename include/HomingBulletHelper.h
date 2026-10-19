//
// Created by g on 16/10/2026.
//

#ifndef RAYLIB_STG_HOMINGBULLETHELPER_H
#define RAYLIB_STG_HOMINGBULLETHELPER_H
#include "Enemy.h"
#include "HomingBullet.h"

class HomingBulletHelper : public Enemy {
private:
    std::shared_ptr<PoolingVector<HomingBullet>> bulletPool;
    std::vector<HomingBullet*> bullets;
    std::vector<Vector2> bulletPositions{};
    Vector2 currentDirection{};
    static constexpr float maxRotationAngle = 0.12f;
    float currentMaxRotationAngle = maxRotationAngle;
    float currentSpeed = 1;
    int stepsElapsed = 0;
    public:
    HomingBulletHelper(std::shared_ptr<PoolingVector<HomingBullet>> _bulletPool) {
        bulletPool = _bulletPool;
    };
    bool doPhysics() override {

        const Vector2 playerFinalPos = PlayerHandler::GetPlayer()->GetFinalPos();
        if (stepsElapsed++ % 5 == 0) {
            if (bullets.size() < 5) {
                HomingBullet* newBullet = &bulletPool->spawn();
                newBullet->spawn({});
                bullets.emplace_back(newBullet);
                bulletPositions.emplace_back(Vector2{});
            }
            for (size_t i = bulletPositions.size() - 1; i > 0; i--) {
                bulletPositions[i] = bulletPositions.at(i - 1);
                bullets[i]->SetPosition(bulletPositions.at(i));
            }
        }
        if (!bullets.at(0)->CheckPosition()) {
            bullets.at(0)->despawn();
            if (bullets.size() == 1) {
                bullets.erase(bullets.begin());
                return false;
            }
            for (size_t i = bulletPositions.size() - 1; i > 0; i--) {
                bulletPositions[i] = bulletPositions.at(i - 1);
            }
            bullets.erase(bullets.begin());
            bulletPositions.pop_back();
        }
        const Vector2 leadBulletPos = bulletPositions.at(0);
        const float desiredRotationAngle = Vector2Angle(currentDirection, Vector2Normalize(Vector2Subtract(playerFinalPos, leadBulletPos)));
        if (std::abs(desiredRotationAngle) > currentMaxRotationAngle)
            currentDirection = Vector2Rotate(currentDirection, std::copysign(currentMaxRotationAngle, desiredRotationAngle));
        else
            currentDirection = Vector2Rotate(currentDirection, desiredRotationAngle);
        bulletPositions.at(0) = Vector2Add(leadBulletPos, currentSpeed * currentDirection);
        bullets.at(0)->SetPosition(bulletPositions.at(0));
        currentMaxRotationAngle -= 0.0003f;
        currentSpeed += 0.02f;

        if (!GlobalVariables::GetCurrentPhase()->CanSpawnBullets())
            return false;
        return true;
    }

    void spawn(const EnemySpawnParametres _params) override {
        bullets.clear();
        bulletPositions.clear();
        bullets.emplace_back(&bulletPool->spawn());
        bullets.at(0)->spawn(_params.pos);
        bulletPositions.emplace_back(_params.pos);
        currentDirection = Vector2Normalize(Vector2Subtract(PlayerHandler::GetPlayer()->GetFinalPos(), _params.pos));
        currentSpeed = 1;
        position = _params.pos;
    };

    void spawn(const Vector2 _position) override {
        spawn(EnemySpawnParametres{_position});
    };

    void spawn(const Vector2 _position, const u_int _scoreValue) override {
        spawn(_position);
    };
};
#endif //RAYLIB_STG_HOMINGBULLETHELPER_H
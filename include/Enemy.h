//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_ENEMY_H
#define RAYLIB_STG_ENEMY_H
#include "StepThinker.h"
#include "PlayerBullet.h"
#include "PlayerBullets.h"

class Enemy : public Spawnable {
protected:
    Vector2 position = {};
    static inline const ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Rectangle collider = {}; //The Enemy's collider
public:
    [[nodiscard]] bool checkPlayerBulletCollision() const {
        const int activePlayerBullets = PlayerBullets::getPlayerBullets()->getNumActive();
        if (activePlayerBullets <= 0) {
            return false;
        }
        std::vector<PlayerBullet>& playerBulletsVector = PlayerBullets::getPlayerBullets()->getVector();

        for (int i = 0; i < activePlayerBullets;) {
            const Rectangle *bulletCollider = playerBulletsVector.at(i).getCollider();
            if (CheckCollisionRecs(collider, *bulletCollider)) {
                PlayerBullets::destroyPlayerBullet(i);
                return true;
            }
            i++;
        }
        return false;
    }

    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(sprite, position);
    }

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        return !checkPlayerBulletCollision();
    }

    void spawn(const Vector2 _position) override {
        position = _position;
    }

    void spawn(const Vector2 _position, int scoreValue) override {
        position = _position;
    }
};
#endif //RAYLIB_STG_ENEMY_H
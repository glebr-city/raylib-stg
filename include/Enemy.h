//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_ENEMY_H
#define RAYLIB_STG_ENEMY_H

#include "PlayerBullet.h"
#include "PlayerBullets.h"

struct EnemySpawnParametres
{
    Vector2 pos = {};
    u_int scoreValue = 50;
    u_int id = 0;
};


class Enemy : public Spawnable {
private:
    const u_int HIT_FLASH_DURATION = 120;
protected:
    Vector2 position = {};
    static inline const ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Rectangle collider = {}; //The Enemy's collider
    u_int scoreValue = 50;
    u_int id = 0; //Special IDs for keeping track of specific enemies, used by PhaseHelpers.
    int currentFlashDuration = 0;
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
        if (currentFlashDuration > 0)
        {
            currentFlashDuration--;
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .flashing = true});
        }
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position});
    }

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        return !checkPlayerBulletCollision();
    }

    void spawn(const EnemySpawnParametres _params) {
        position = _params.pos;
        collider.x = position.x;
        collider.y = position.y;
        scoreValue = _params.scoreValue;
        id = _params.id;
    }

    void spawn(Vector2 _position) override
    {
        spawn(EnemySpawnParametres{_position});
    }

    void spawn(Vector2 _position, u_int _scoreValue) override
    {
        spawn(EnemySpawnParametres{_position});
    }


    virtual bool takeDamage() // Return false to kill the enemy.
    {
        startDamageAnimation();
        die();
        return false;
    }

    virtual void startDamageAnimation()
    {
        currentFlashDuration = HIT_FLASH_DURATION;
    }

    void die()
    {
        ScoreHandler::addScore(scoreValue);
        GlobalVariables::getCurrentPhase()->enemyKilled(id);
    }

    virtual void despawn()
    {
        GlobalVariables::getCurrentPhase()->enemyDespawned(id);
    }
};
#endif //RAYLIB_STG_ENEMY_H
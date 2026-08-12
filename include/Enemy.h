//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_ENEMY_H
#define RAYLIB_STG_ENEMY_H

#include "EphemeraHandler.h"
#include "PlayerBullet.h"
#include "PlayerBullets.h"

struct EnemySpawnParametres
{
    Vector2 pos = {};
    u_int id = 0;
};


class Enemy : public Spawnable {
public:
    struct EnemyDeathInfo
    {
        EnemyDeathInfo(const EphemeraHandler::EPHEMERAE _t = EphemeraHandler::EXPLOSION_SMALL, const LAYERS _l = LAYER_ENEMY)
        {
            t = _t;
            l = _l;
        }
        EphemeraHandler::EPHEMERAE t;
        LAYERS l;
    };
private:
    const u_int HIT_FLASH_DURATION = 90;
protected:
    int health = 1;
    static constexpr ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Rectangle collider = {}; //The Enemy's collider
    uint scoreValue = 500;
    u_int id = 0; //Special IDs for keeping track of specific enemies, used by PhaseHelpers.
    int currentFlashDuration = 0;
    EnemyDeathInfo deathInfo = {};
public:
    explicit Enemy(const uint _scoreValue = 500, const Rectangle _collider = {}, const int _health = 1, const EnemyDeathInfo _deathInfo = {})
    {
        scoreValue = _scoreValue;
        collider = _collider;
        health = _health;
        deathInfo = _deathInfo;
    }
    void checkPlayerCollision() const
    {
        if (CheckCollisionPointRec(PlayerHandler::GetPlayer().get()->GetFinalPos(), collider))
            DamageHandler::hitPlayer();
    }
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
    void doPostStep() override {
        if (currentFlashDuration > 0)
        {
            currentFlashDuration--;
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .flashing = true});
        }
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position});
    }

    bool doPhysics() override {
        checkPlayerCollision();
        if (checkPlayerBulletCollision())
            return takeDamage();
        return true;
    }



    void spawn(const EnemySpawnParametres _params) {
        position = _params.pos;
        collider.x += position.x - collider.width / 2;
        collider.y += position.y - collider.height / 2;
        id = _params.id;
    }

    void spawn(const Vector2 _position) override
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
        if (--health <= 0)
        {
            die();
            return false;
        }
        return true;
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
        //GlobalVariables::getCurrentPhase()->enemyDespawned(id);
    }

     [[nodiscard]] u_int GetID() const
    {
        return id;
    }

    EnemyDeathInfo* GetDeathInfo()
    {
        return &deathInfo;
    }
};
#endif //RAYLIB_STG_ENEMY_H
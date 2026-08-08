//
// Created by n on 07/08/2026.
//

#ifndef RAYLIB_STG_BOSS_H
#define RAYLIB_STG_BOSS_H
#include "Enemy.h"
#include "HUDHandler.h"

class Boss : public Enemy
{
protected:
    int maxHealth = -1;
public:
    explicit Boss(const uint _scoreValue = 500, const Rectangle _collider = {}, const int _health = 1) : Enemy(_scoreValue, _collider, _health) {}

    void setHealth(const int _maxHealth, const int _health)
    {
        health = _health;
        maxHealth = _maxHealth;
        HUDHandler::SetBossHealth(&health, maxHealth);
    }

    void SetHealth(const int _maxHealth)
    {
        setHealth(_maxHealth, _maxHealth);
    }

    int* GetHealth()
    {
        return &health;
    }
};
#endif //RAYLIB_STG_BOSS_H
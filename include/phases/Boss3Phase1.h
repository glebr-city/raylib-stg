//
// Created by g on 26/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE1_H
#define RAYLIB_STG_BOSS3PHASE1_H
#include "Boss3.h"
#include "PhaseHelper.h"

class Boss3Phase1 : public PhaseHelper {
    static constexpr int PHASE_1_HEALTH = 154;
    static constexpr int PHASE_1_TIME = 3300;
    static constexpr Boss3::BOSS_3_PHASES PHASE_1_BOSS_PHASE = Boss3::PHASE_1;
    Boss3::BOSS_3_PHASES preFightPhase = Boss3::PRE_FIGHT;
protected:
    int* bossHealth = nullptr;
    int maxHealth = 140;
    int maxTimer = 3000;
    int bossTimer = maxTimer;
    Boss3::BOSS_3_PHASES bossPhase = Boss3::PHASE_1;
    std::shared_ptr<Boss3> boss3 = nullptr;
    int phaseSpriteDamage = 0;
private:
    void attemptFindingBoss3()
    {

        for (const auto & _spawnedEnemy : *SpawnedEnemies::getSpawnedEnemies())
        {
            if (_spawnedEnemy->GetID() == 401)
            {
                boss3 = std::static_pointer_cast<Boss3>(_spawnedEnemy);
                return;
            }
        }
        boss3 = std::make_shared<Boss3>();
        boss3->spawn({.pos=Vector2(60, 30), .id = 401});
        boss3->SetPhase(preFightPhase);
        SpawnedEnemies::spawnEnemy(boss3);
    }
public:
    explicit Boss3Phase1(std::string _phaseName = "Boss3Phase1", const int _maxHealth = PHASE_1_HEALTH, const int _maxTimer = PHASE_1_TIME, const Boss3::BOSS_3_PHASES _bossPhase = PHASE_1_BOSS_PHASE, const int _spriteDamage = 0, const Boss3::BOSS_3_PHASES _preFightPhase = Boss3::PRE_FIGHT) : PhaseHelper(std::move(_phaseName), {0, -680}, {0, 0}, STAGE_3_BACKGROUND)
    {
        maxHealth = _maxHealth;
        maxTimer = _maxTimer;
        bossPhase = _bossPhase;
        bossTimer = maxTimer;
        preFightPhase = _preFightPhase;
        phaseSpriteDamage = _spriteDamage;
    }

    void InitPhase() override
    {
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        BackgroundHandler::SetBackgroundPosition(defaultBackgroundPosition);
        attemptFindingBoss3();
        bossHealth = boss3->GetHealth();
        boss3->SetPhase(preFightPhase);
        boss3->SetSpriteDamage(phaseSpriteDamage);
    }

    bool doPhysics() override
    {
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss3->SetHealth(maxHealth);
            boss3->SetPhase(bossPhase);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            SoundHandler::PlaySound(EXPLOSION_1);
            cancelBullets();
            GameHandler::NextPhase();
            return false;
        }
        if (*bossHealth <= 0)
        {
            SoundHandler::PlaySound(EXPLOSION_1);
            cancelBullets();
            ScoreHandler::addScore(10000, false);
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override {};
    void enemyDespawned(u_int _id) override {};
};
#endif //RAYLIB_STG_BOSS3PHASE1_H
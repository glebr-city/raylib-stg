//
// Created by n on 28/09/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE1_H
#define RAYLIB_STG_BOSS2PHASE1_H
#include "Boss2.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"
#include "Boss1SmallBullet.h"
#include "SimpleBullet1Slow.h"
#include "Boss1FastBurstBullet.h"

class Boss2Phase1 : public PhaseHelper
{
    static constexpr int PHASE_1_HEALTH = 154;
    static constexpr int PHASE_1_TIME = 3300;
    static constexpr Boss2::BOSS_2_PHASES PHASE_1_BOSS_PHASE = Boss2::PHASE_1;
    Boss2::BOSS_2_PHASES preFightPhase = Boss2::PRE_FIGHT;
protected:
    int* bossHealth = nullptr;
    int maxHealth = 140;
    int maxTimer = 3000;
    int bossTimer = maxTimer;
    Boss2::BOSS_2_PHASES bossPhase = Boss2::PHASE_1;
    std::shared_ptr<Boss2> boss2 = nullptr;
    int phaseSpriteDamage = 0;
private:
    void attemptFindingBoss2()
    {

        for (const auto & _spawnedEnemy : *SpawnedEnemies::getSpawnedEnemies())
        {
            if (_spawnedEnemy->GetID() == 301)
            {
                boss2 = std::static_pointer_cast<Boss2>(_spawnedEnemy);
                return;
            }
        }
        boss2 = std::make_shared<Boss2>();
        boss2->spawn({.pos=BackgroundHandler::GetRelativePos(Vector2(60, -1900)), .id = 301});
        boss2->SetPhase(preFightPhase);
        SpawnedEnemies::spawnEnemy(boss2);
    }
public:
    explicit Boss2Phase1(std::string _phaseName = "Boss2Phase1", const int _maxHealth = PHASE_1_HEALTH, const int _maxTimer = PHASE_1_TIME, const Boss2::BOSS_2_PHASES _bossPhase = PHASE_1_BOSS_PHASE, const int _spriteDamage = 0, const Boss2::BOSS_2_PHASES _preFightPhase = Boss2::PRE_FIGHT) : PhaseHelper(std::move(_phaseName), {0, -1800}, {0, 0}, STAGE_2_BACKGROUND)
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
        attemptFindingBoss2();
        bossHealth = boss2->GetHealth();
        boss2->SetPhase(preFightPhase);
        boss2->SetSpriteDamage(phaseSpriteDamage);
    }

    bool doPhysics() override
    {
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss2->SetHealth(maxHealth);
            boss2->SetPhase(bossPhase);
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
#endif //RAYLIB_STG_BOSS2PHASE1_H
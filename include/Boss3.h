//
// Created by n on 26/10/2026.
//

#ifndef RAYLIB_STG_BOSS3_H
#define RAYLIB_STG_BOSS3_H
#include "AcceleratingBullet2.h"
#include "Boss.h"
#include "Boss3ColourShiftBullet.h"
#include "Boss3Phase3Bullet1.h"
#include "Boss3Phase3Explosive.h"
#include "RadialBullet1.h"
#include "SimpleBullet1VariableSpeed.h"

class Boss3 : public Boss
{
public:
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1,
        PHASE_2,
        PRE_PHASE_3,
        PHASE_3,
        PHASE_4,
        PRE_PHASE_5,
        PHASE_5,
        PHASE_DEFEAT
    }BOSS_3_PHASES;
private:
    static constexpr Color phase3BulletColour = {30, 30, 255, 255};
    static constexpr int phase5OffsetDistance = 25;
    Color drawnColour = WHITE;
    int baseSpriteYOffset = 0; //Used for damage sprites
    BOSS_3_PHASES bossPhase = PRE_FIGHT;
    unsigned int stepsElapsed = 0;
    float phase1CurrentRotation = 0;
    float phase2CurrentRotation = 0;
    float phase3CurrentRotation = 0;
    float phase4CurrentRotation = 0;
    float phase5CurrentRotation = 0;
    Vector2 phase4MovementVector{};
    Vector2 phase4MovementTarget{};
    Vector2 phase5CurrentOffsetDirection{};
    bool phase4CounterClockwise = false;
    std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>> simpleBullet1VariableSpeedPool;
    std::shared_ptr<PoolingVector<Boss3ColourShiftBullet>> colourShiftBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet2VariableSpeed>> simpleBullet2VariableSpeedPool;
    std::shared_ptr<PoolingVector<AcceleratingBullet2>> acceleratingBullet2Pool;
    std::shared_ptr<PoolingVector<Boss3Phase3Bullet1>> phase3Pool;
    std::vector<Boss3Phase3Bullet1*> phase3FiredBullets;
    std::shared_ptr<PoolingVector<RadialBullet1>> radialBulletPool;

    void initPhase(const BOSS_3_PHASES _newPhase) {
        stepsElapsed = -1;
        switch (_newPhase) {
            case PRE_FIGHT:
                break;
            case PHASE_1:
                phase1CurrentRotation = (RNGHandler::GetSeed() % 354) * 0.001f;
                if (simpleBullet1VariableSpeedPool == nullptr) {
                    simpleBullet1VariableSpeedPool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed> >(500);
                    GlobalPools::AddPool(simpleBullet1VariableSpeedPool);
                }
                if (colourShiftBulletPool == nullptr) {
                    colourShiftBulletPool = std::make_shared<PoolingVector<Boss3ColourShiftBullet> >(100);
                    GlobalPools::AddPool(colourShiftBulletPool);
                }
                break;
            case PHASE_2:
                phase2CurrentRotation = (RNGHandler::GetSeed() % 354) * 0.001f;
                if (simpleBullet1VariableSpeedPool == nullptr) {
                    simpleBullet1VariableSpeedPool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed> >(500);
                    GlobalPools::AddPool(simpleBullet1VariableSpeedPool);
                }
                if (colourShiftBulletPool == nullptr) {
                    colourShiftBulletPool = std::make_shared<PoolingVector<Boss3ColourShiftBullet> >(100);
                    GlobalPools::AddPool(colourShiftBulletPool);
                }
                if (simpleBullet2VariableSpeedPool == nullptr) {
                    simpleBullet2VariableSpeedPool = std::make_shared<PoolingVector<SimpleBullet2VariableSpeed> >(500);
                    GlobalPools::AddPool(simpleBullet2VariableSpeedPool);
                }
                break;
            case PHASE_3:
                phase3CurrentRotation = (RNGHandler::GetSeed() % 354) * 0.001f;
                if (phase3Pool == nullptr) {
                    phase3Pool = std::make_shared<PoolingVector<Boss3Phase3Bullet1> >(200);
                    GlobalPools::AddPool(phase3Pool);
                }
                if (acceleratingBullet2Pool == nullptr) {
                    acceleratingBullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet2> >(500);
                    GlobalPools::AddPool(acceleratingBullet2Pool);
                }
                break;
            case PHASE_4:
                phase4CounterClockwise = false;
                phase3FiredBullets.clear();
                phase4MovementVector = {};
                phase4CurrentRotation = RNGHandler::GetSeed() % 200 * 0.001f;
                if (radialBulletPool == nullptr) {
                    radialBulletPool = std::make_shared<PoolingVector<RadialBullet1> >(500);
                    GlobalPools::AddPool(radialBulletPool);
                }
                break;
            case PRE_PHASE_5:
                phase5CurrentOffsetDirection = {0, -1};
                break;
        case PHASE_5:
                phase3CurrentRotation = (RNGHandler::GetSeed() % 354) * 0.001f;
                phase5CurrentOffsetDirection = {0, -1};
                phase5CurrentRotation = (RNGHandler::GetSeed() % 354) * 0.001f;
                if (simpleBullet1VariableSpeedPool == nullptr) {
                    simpleBullet1VariableSpeedPool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed> >(500);
                    GlobalPools::AddPool(simpleBullet1VariableSpeedPool);
                }
                if (colourShiftBulletPool == nullptr) {
                    colourShiftBulletPool = std::make_shared<PoolingVector<Boss3ColourShiftBullet> >(100);
                    GlobalPools::AddPool(colourShiftBulletPool);
                }
                if (radialBulletPool == nullptr) {
                    radialBulletPool = std::make_shared<PoolingVector<RadialBullet1> >(500);
                    GlobalPools::AddPool(radialBulletPool);
                }
            case PHASE_DEFEAT:
                break;
            default:
                break;
        }
    }
public:
    explicit Boss3(const int _health = 1)
    : Boss(500, {0, 0, 22, 28}, _health) {
    }


    bool doPhysics() override {
        stepsElapsed++;
        collider.x = position.x - (collider.width / 2);
        collider.y = position.y - (collider.height / 2);
        switch (bossPhase)
        {
            case PRE_FIGHT:
                return true;
            case PHASE_1:
                if (stepsElapsed % 130 < 110) {
                    if (stepsElapsed % 130 == 0)
                        SoundHandler::PlaySound(SOUNDS::FINGER_RUB_STRETCHED);
                    if (stepsElapsed % 3 == 0) {
                        if (stepsElapsed % 6 == 0)
                            SoundHandler::PlaySound(THUMP_3);
                        const Vector2 shotDirection = Vector2Rotate(Vector2Normalize(Vector2(std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1, 1)), phase1CurrentRotation);
                        for (int i = 0; i < 5; i++) {
                            const Color bulletColour = {static_cast<unsigned char>(i * 30), static_cast<unsigned char>(i * 30), 255, 255};
                            simpleBullet1VariableSpeedPool->spawn().spawn(0.4f + (i * 0.3f), position, shotDirection, bulletColour);
                        }
                        phase1CurrentRotation += 0.212930168743;
                    }
                } else if (stepsElapsed % 130 == 120) {
                    SoundHandler::PlaySound(SLIDE_1);
                    const Vector2 startingVector = Vector2Rotate({0, 1}, (RNGHandler::GetSeed() % 1000 - 500) * 0.0003);
                    for (int k = 0; k < 2; k++) {
                        for (int i = -1; i < 2; i++) {
                            for (int j = 0; j < 30; j++) {
                                const float rotation = j * 0.209439510239 + i * 0.05;
                                colourShiftBulletPool->spawn().spawn(1.5f + (i * 0.1f), Vector2(position.x+i*3 - k, position.y + i*3 + k), Vector2Rotate(startingVector, rotation), BLUE);
                            }
                        }
                    }
                }
                checkPlayerCollision();
                if (checkPlayerBulletCollision())
                    takeDamage();
                return true;
            case PHASE_2:
                    if (stepsElapsed % 40 == 0) {
                        SoundHandler::PlaySound(THUMP_1);
                        SoundHandler::PlaySound(BANG_2);
                        Vector2 playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                        const Vector2 shotDirection = Vector2Normalize({playerPos.x - position.x, playerPos.y - position.y});
                        const Vector2 sidewaysVector = Vector2Rotate(shotDirection, 1.57079632679);
                        for (int i = -2; i <= 2; i+=2) {
                            const Vector2 shotPosition = Vector2Add(position, i*2*sidewaysVector);
                            colourShiftBulletPool->spawn().spawn(1.7f, shotPosition, shotDirection, BLUE);
                        }
                    }
                    if (stepsElapsed % 30 == 0) {
                        for (int k = -1; k <= 1; k++) {
                            const Vector2 shotDirection = Vector2Rotate(Vector2Normalize(Vector2(std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1, 1)), phase2CurrentRotation + k * 2.09439510239);
                            const Vector2 spawnPosition = Vector2Add(position, shotDirection * 5);
                            for (int i = 0; i < 7; i++) {
                                const Color bulletColour = {static_cast<unsigned char>(i * 20), static_cast<unsigned char>(i * 20), 255, 255};
                                for (int j = -i; j < i; j++) {
                                    simpleBullet2VariableSpeedPool->spawn().spawn(1 + (i * 0.1f), spawnPosition, Vector2Rotate(shotDirection, j * 0.06f), bulletColour);
                                }
                            }
                        }
                        phase2CurrentRotation += 0.728318530718;
                    }
                checkPlayerCollision();
                if (checkPlayerBulletCollision())
                    takeDamage();
                return true;
            case PRE_PHASE_3:
                if (Vector2DistanceSqr(position, {60, 90}) > 1) {
                    position = Vector2MoveTowards(position, {60, 90}, 1);
                } else {
                    position = {60, 90};
                }
                return true;
            case PHASE_3:
                for (int firedBullet = 0; firedBullet < phase3FiredBullets.size(); firedBullet++) {
                    if (phase3FiredBullets.at(firedBullet)->GetHasStopped()) {
                        Boss3Phase3Explosive newExplosive{acceleratingBullet2Pool};
                        const Vector2 explosivePos = phase3FiredBullets.at(firedBullet)->GetPosition();
                        const Vector2 explosiveMovementDirection = Vector2Normalize(explosivePos - position);
                        newExplosive.spawn(explosivePos, explosiveMovementDirection, phase3BulletColour);
                        SpawnedEnemies::spawnEnemy(std::make_shared<Boss3Phase3Explosive>(std::move(newExplosive)));
                        phase3FiredBullets.erase(phase3FiredBullets.begin() + firedBullet);
                    } else if (phase3FiredBullets.at(firedBullet)->GetHasDespawned())
                        phase3FiredBullets.erase(phase3FiredBullets.begin() + firedBullet);
                }
                if (stepsElapsed % 4 == 0) {
                    if (stepsElapsed % 8 == 0)
                        SoundHandler::PlaySound(CLICK_1);
                    for (int j = -1; j <= 1; j += 2) {
                        const Vector2 shotDirection = Vector2Rotate(
                            Vector2Normalize(Vector2(std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1, j)),
                            phase3CurrentRotation);
                        for (int i = 0; i < 1; i++) {
                            const int stepToStop =
                                    2 + RNGHandler::GetSeed() % 3 * 10 + RNGHandler::GetSeed() % 4 * 50 +
                                    RNGHandler::GetSeed() % 6;
                            Boss3Phase3Bullet1 *newBullet = &phase3Pool->spawn();
                            newBullet->spawn(stepToStop, Vector2Add(position, shotDirection * 3), shotDirection,
                                             phase3BulletColour);
                            phase3FiredBullets.emplace_back(newBullet);
                        }
                    }
                    phase3CurrentRotation += 0.06f;
                }
                checkPlayerCollision();
                if (checkPlayerBulletCollision())
                    takeDamage();
                return true;
            case PHASE_4:
                if (stepsElapsed % 900 == 650) {
                    if (!phase4CounterClockwise) {
                        phase4MovementTarget = {60, 60};
                    } else {
                        phase4MovementTarget = {60, 120};
                    }
                }
            if (stepsElapsed % 900 > 650)
            {
                position = Vector2MoveTowards(position, phase4MovementTarget, 2);
                if (stepsElapsed % 900 == 750 || stepsElapsed % 900 == 800)
                {
                    SoundHandler::PlaySound(FINGER_RUB);
                    if (stepsElapsed % 900 == 800)
                        phase4CounterClockwise = !phase4CounterClockwise;
                    phase4CurrentRotation = RNGHandler::GetSeed() % 200 * 0.0005f;
                    for (int j = -1; j <= 1; j += 2)
                    {
                        for (int i = 0; i < 24; i++) {
                            if (i % 3 == 0)
                                continue;
                            const Vector2 shotDirection = Vector2Rotate(Vector2Normalize(Vector2(std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1, 1)), phase4CurrentRotation);
                            const Color bulletColour = {static_cast<unsigned char>(i * 5), static_cast<unsigned char>(i * 10), 200, 255};
                            radialBulletPool->spawn().spawn(0.5f + (i * 0.03f), j * (0.02f - i * 0.001f), position, shotDirection, bulletColour);
                            phase4CurrentRotation += 1.0471975512;
                        }
                    }
                }
            } else
            {
                position += phase4MovementVector;
                if (position.x < 5 || position.x > 115)
                    phase4MovementVector.x *= -1;
                if (position.y < 5 || position.y > 185)
                    phase4MovementVector.y *= -1;
                if (stepsElapsed % 200 == 100)
                    phase4MovementVector = Vector2(copysign(0.8f, 60 - position.x) + (RNGHandler::GetSeed() % 100 - 50) * 0.005f, copysign(0.8f, 60 - position.y) + (RNGHandler::GetSeed() % 100 - 50) * 0.005f);
                else if (stepsElapsed % 200 == 0)
                    phase4MovementVector = {};
                if (stepsElapsed % 200 < 110) {
                    if (stepsElapsed % 10 == 0) {
                        SoundHandler::PlaySound(SOUNDS::BANG_1);
                        float shotRotation = std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1;
                        if (phase4CounterClockwise)
                            shotRotation *= -1;
                        const Vector2 shotDirection = Vector2Rotate(Vector2Normalize(Vector2(shotRotation, 1)), phase4CurrentRotation);
                        for (int i = 0; i < 4; i++) {
                            const Color bulletColour = {static_cast<unsigned char>(i * 30), static_cast<unsigned char>(i * 30), 255, 255};
                            float angularSpeed = -0.02f + (i * 0.005f);
                            if (phase4CounterClockwise)
                                angularSpeed *= -1;
                            radialBulletPool->spawn().spawn(0.4f + (i * 0.2f), angularSpeed, position, shotDirection, bulletColour);
                        }
                        if (phase4CounterClockwise)
                            phase4CurrentRotation -= 0.812930168743;
                        else
                            phase4CurrentRotation += 0.812930168743;
                    }
                }
            }
                checkPlayerCollision();
                if (checkPlayerBulletCollision())
                    takeDamage();
                return true;
            case PRE_PHASE_5:
                    position = Vector2MoveTowards(position, Vector2Add({60, 90}, phase5CurrentOffsetDirection * phase5OffsetDistance), 1);
                return true;
        case PHASE_5:
                phase5CurrentOffsetDirection = Vector2Rotate(phase5CurrentOffsetDirection, -0.007f);
                position = Vector2Add({60, 90}, phase5CurrentOffsetDirection * phase5OffsetDistance);
                if (stepsElapsed % 120 == 50) {
                    SoundHandler::PlaySound(SOUNDS::BANG_1);
                    for (int j = 0; j < 4; j++) {
                        const Vector2 shotDirection = Vector2Rotate(
                            Vector2Normalize(Vector2(std::sin(stepsElapsed % 120 * 0.0628318530718) * 0.1, 1)),
                            phase5CurrentRotation);
                        for (int i = 0; i < 3; i++) {
                            const Color bulletColour = {
                                static_cast<unsigned char>(220 + i * 10), static_cast<unsigned char>(150 - i * 2), static_cast<unsigned char>(220 + i * 10), 255
                            };
                            simpleBullet1VariableSpeedPool->spawn().spawn(
                                0.5f + (i * 0.05f), position, shotDirection, bulletColour);
                        }
                        phase5CurrentRotation += 1.57079632679;
                    }
                    phase5CurrentRotation += 0.3;
                }
                if (stepsElapsed % 18 == 0) {
                    SoundHandler::PlaySound(CLICK_1);
                    for (int k = -1; k <=1; k += 2) {
                        for (int j = -1; j <= 1; j += 2) {
                            const Vector2 shotDirection = Vector2Rotate(
                                Vector2Normalize(Vector2(std::sin(stepsElapsed % 240 * 0.0628318530718) * 0.1, j)),
                                phase3CurrentRotation);
                            radialBulletPool->spawn()
                            .spawn(0.8f, k * -0.001f, Vector2Add(position, shotDirection * 3),shotDirection,{150, 50, 255, 255});
                            radialBulletPool->spawn()
                            .spawn(0.8f, k * -0.001f, Vector2Add(position, shotDirection * 3),Vector2Rotate(shotDirection, 1.57079632679),{150, 50, 255, 255});
                            simpleBullet1VariableSpeedPool->spawn()
                            .spawn(0.8f, Vector2Add(position, shotDirection * 3),shotDirection,{150, 50, 255, 255});
                            simpleBullet1VariableSpeedPool->spawn()
                            .spawn(0.8f, Vector2Add(position, shotDirection * 3),Vector2Rotate(shotDirection, 1.57079632679),{150, 50, 255, 255});
                            phase3CurrentRotation -= 0.032f;
                        }
                    }
                }

                if (stepsElapsed % 120 == 0)
                {
                    SoundHandler::PlaySound(SOUNDS::SLIDE_2);
                    phase4CurrentRotation = RNGHandler::GetSeed() % 200 * 0.0005f;
                    for (int j = -1; j <= 1; j += 2)
                    {
                        for (int i = 0; i < 6; i++) {
                            const Vector2 shotDirection = Vector2Rotate(Vector2Normalize(Vector2(std::sin(stepsElapsed % 100 * 0.0628318530718) * 0.1, 1)), phase4CurrentRotation);
                            const Color bulletColour = {static_cast<unsigned char>(150 - i * 5), static_cast<unsigned char>(100 + i * 25), 50, 255};
                            radialBulletPool->spawn().spawn(0.5f, j * (0.01f - i * 0.0005f), position, shotDirection, bulletColour);
                            phase4CurrentRotation += 1.0471975512;
                        }
                    }
                }
                checkPlayerCollision();
                if (checkPlayerBulletCollision())
                    takeDamage();
                return true;
            default: return true;
        }
    }

    void doPostStep() override
    {
        drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 45)
            drawnColour = RED;
        SpriteHandler::QueueMyAnimatedSprite({.i=BOSS_3_TENDRILS, .pos=position, .yOffset=baseSpriteYOffset, .l = LAYER_GROUNDED, .col = drawnColour});
        SpriteHandler::QueueMyAnimatedSprite({.i=BOSS_3_BASE, .pos=position, .yOffset=baseSpriteYOffset, .l = LAYER_GROUNDED, .col = drawnColour});
    }

    void SetPhase(const BOSS_3_PHASES _newPhase)
    {
        bossPhase = _newPhase;
        initPhase(_newPhase);
    }
    void SetSpriteDamage(const uint_fast8_t _damage)
    {
        baseSpriteYOffset = _damage;
    }
};
#endif //RAYLIB_STG_BOSS3_H
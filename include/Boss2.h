//
// Created by n on 28/09/2026.
//

#ifndef RAYLIB_STG_BOSS2_H
#define RAYLIB_STG_BOSS2_H
#include "Boss.h"
#include "Boss2Automaton.h"
#include "Boss2CrossBullet1.h"
#include "Boss2SmallBullet.h"

class Boss2AutomatonPinkBullet;
class Boss1FastBurstBullet;
class SimpleBullet1Slow;
class Boss1SmallBullet;

class  Boss2 : public Boss
{
public:
    constexpr static int COLLIDER_Y_OFFSET = -20;
    constexpr static int COLLIDER_2_Y_OFFSET = 17;
    constexpr static int maxMovement = 45; //How far, in one direction on the X-axis, may the boss move?
    constexpr static Color PARTS_COLOUR = {183, 0, 0, 255};
    constexpr static Color CROSS_SHOT_COLOUR = {200, 0, 59, 255};
    constexpr static uint8_t PHASE_1_FIRE_RATE = 3;
    constexpr static uint8_t PHASE_2_FIRE_RATE = 16;
    constexpr static uint8_t PHASE_3_FIRE_RATE = 90;
    constexpr static uint8_t PHASE_4_FIRE_RATE = 24;
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1,
        PHASE_2,
        PRE_PHASE_3,
        PHASE_3,
        PHASE_4,
        PHASE_DEFEAT
    }BOSS_2_PHASES;

    typedef enum {
        LOW = 0,
        MIDDLE,
        HIGH
    } PHASE_3_FIRE_SEGMENTS;
private:
    Rectangle collider2; //Due to the boss' shape, a second collider is required!
    std::shared_ptr<Boss2Automaton> automaton1;
    std::shared_ptr<Boss2Automaton> automaton2;
    std::shared_ptr<PoolingVector<Boss2SmallBullet>> smallBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet1Slow>> simpleBullet1SlowPool;
    std::shared_ptr<PoolingVector<Boss1FastBurstBullet>> simpleBullet1FastPool;
    std::shared_ptr<PoolingVector<Boss2AutomatonPinkBullet>> automatonPinkBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet2VariableSpeed>> automatonVariableSpeedBulletPool;
    std::shared_ptr<PoolingVector<Boss2CrossBullet1>> crossBullet1Pool;
    BOSS_2_PHASES bossPhase = PRE_FIGHT;
    static constexpr std::array<Vector2, 11> smallPartOffsets = {
        Vector2(-8.5, 7),
        Vector2(-2.5, 7),
        Vector2(2.5, 7),
        Vector2(8.5, 7),
        Vector2(-5.5, 10),
        Vector2(5.5, 10),
        Vector2(-8.5, 13),
        Vector2(-2.5, 13),
        Vector2(2.5, 13),
        Vector2(8.5, 13),
    };
    static constexpr std::array<Vector2, 4> crossOffsets = {
        Vector2(-23.5, -16),
        Vector2(-11.5, -3),
        Vector2(11.5, -3),
        Vector2(23.5, -16),
    };
    std::array<int, 11> currentSmallPartsGlowSteps{};
    std::array<int, 4> currentCrossGlowSteps{};
    uint stepsElapsed = 0;
    uint8_t currentSmallPart = 0;
    uint8_t currentCross = 0;
    int smallPartsGlowSteps = 15; //Glow for this many steps after firing
    int crossGlowSteps = 15; //Glow for this many steps after firing
    int baseSpriteYOffset = 0;
    Color drawnColour = WHITE;
    Vector2 movementVector = {};

    void fireSpread(const Vector2 _pos, const Vector2 _dir)
    {
        SoundHandler::PlaySound(0, SLIDE_3, false);
        for (int i = -5; i < 5; i++)
        {
            const Vector2 translatedPos = Vector2Add(_pos, {-_dir.y * i * 3, _dir.x * i * 3});
            const Vector2 rotatedDir = Vector2Rotate(_dir, i * 0.2f);
            simpleBullet1SlowPool->spawn().spawn(translatedPos, rotatedDir, CROSS_SHOT_COLOUR);
        }
    }

    void fireBurst(const Vector2 _pos, const Vector2 _dir, const bool fast = false)
    {
        SoundHandler::PlayAnySound({BANG_1, BANG_2}, false, 0);
        for (int i = -3; i < 3; i++)
        {
            const Vector2 translatedPos = Vector2Add(_pos, {-_dir.y * i + i * i, _dir.x * i * 1.5f - i * i});
            const Vector2 rotatedDir = Vector2Rotate(_dir, i * i * 0.02f);
            if (!fast)
                simpleBullet1SlowPool->spawn().spawn(translatedPos, rotatedDir, CROSS_SHOT_COLOUR);
            else
                simpleBullet1FastPool->spawn().spawn(translatedPos, rotatedDir, RED);
        }
    }

    void fireSmallPartShot(uint8_t _currentSmallPart = 11, const float _maxRotation = 0.75f, const float _extraRotation = 0)
    {
        if (_currentSmallPart == 11)
            _currentSmallPart = currentSmallPart;
        const Vector2 playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
        const Vector2 _startingDirection = Vector2Normalize(Vector2{smallPartOffsets[_currentSmallPart].x / 50, 1});
        const Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[_currentSmallPart]);
        const Vector2 _vectorToPlayer = Vector2Subtract(playerPos, _currentBulletSpawnPos);
        const float _rotation = std::clamp(Vector2Angle(_startingDirection, _vectorToPlayer) + _extraRotation, -_maxRotation, _maxRotation);
        currentSmallPartsGlowSteps[_currentSmallPart] = smallPartsGlowSteps;
        smallBulletPool->spawn().spawn(_currentBulletSpawnPos, Vector2Rotate(_startingDirection, _rotation), PARTS_COLOUR);
    }

    void firePhase2CrossShot()
    {
        firePhase2CrossShot(currentCross);
    }
    void firePhase2CrossShot(const uint_fast8_t _currentCross = 4)
    {
        currentCrossGlowSteps[_currentCross] = crossGlowSteps;
        float tempX = crossOffsets[_currentCross].x;
        Color shotColour{CROSS_SHOT_COLOUR.r, CROSS_SHOT_COLOUR.g, static_cast<unsigned char>(CROSS_SHOT_COLOUR.b + (stepsElapsed % 60 * 5)), CROSS_SHOT_COLOUR.a};
        crossBullet1Pool->spawn().spawn(Vector2Add(position, crossOffsets[_currentCross]), Vector2Normalize(Vector2{tempX * 0.015f + 0 * std::signbit(tempX), 1}), shotColour);
    }

    void firePhase3SmallPartShot(const PHASE_3_FIRE_SEGMENTS _segment) {
        Vector2 rotation;
        RNGHandler::StepSeed();
        float yValue = (1 - ((RNGHandler::GetSeed() % 100) * 0.005f));
        switch (_segment){
            case LOW:
                SoundHandler::PlaySound(SOUNDS::BANG_2);
            for (int m = 1; m > -2; m -= 2)
            {
                for (int l = 0; l < 2; l++)
                {
                    for (int j = 0; j < 4; j++) {
                        for (int i = 6; i < 10; i++) {
                            rotation = Vector2Normalize({(smallPartOffsets[i].x + j) / 30 * l, (m * yValue - static_cast<float>(j) / 3)});
                            if (rotation == Vector2Zeros)
                                rotation = Vector2{0, 1};
                            Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[i]);
                            currentSmallPartsGlowSteps[i] = smallPartsGlowSteps;
                            smallBulletPool->spawn().spawn(_currentBulletSpawnPos, rotation, PARTS_COLOUR);
                        }
                    }
                }
            }
                break;
            case MIDDLE:
                SoundHandler::PlaySound(SOUNDS::BANG_1);
                /*for (int a = 4; a < 6; a++) { //Fire aimed shots at the middle of the screen
                    const Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[a]);
                    Vector2 aimedRotation = Vector2Normalize(Vector2Subtract(Vector2{static_cast<float>(57 + (a - 3) * 2), 180}, _currentBulletSpawnPos));
                    const float extraRotation = std::clamp(Vector2Angle(aimedRotation, Vector2Normalize(Vector2Subtract(PlayerHandler::GetPlayer()->GetFinalPos(), _currentBulletSpawnPos))), -0.1f, 0.1f);
                    aimedRotation = Vector2Rotate(aimedRotation, extraRotation);
                    smallBulletPool->spawn().spawn(_currentBulletSpawnPos, aimedRotation, {255, 40, 40, 255});
                }*/
            for (int m = 1; m > -2; m -= 2)
            {
                for (int l = 0; l < 2; l++)
                {
                    for (int k = 1; k < 6; k++)
                    {
                        for (int j = 4; j < 6; j++) {
                            rotation = Vector2Normalize({smallPartOffsets[j].x / (30 * static_cast<float>(k) / 10) * l, m * yValue});
                            for (int i = 4; i < 6; i++) {
                                const Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[i]);
                                currentSmallPartsGlowSteps[i] = smallPartsGlowSteps;
                                smallBulletPool->spawn().spawn(_currentBulletSpawnPos, rotation, PARTS_COLOUR);
                            }
                        }
                    }
                }
            }
                break;
            case HIGH:
                SoundHandler::PlaySound(SOUNDS::BANG_2);
                for (int m = 1; m > -2; m -= 2)
                {
                    for (int l = 0; l < 2; l++)
                    {
                        for (int i = 0; i < 4; i++) {
                            Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[i]);
                            currentSmallPartsGlowSteps[i] = smallPartsGlowSteps;
                            smallBulletPool->spawn().spawn(_currentBulletSpawnPos, Vector2Normalize({smallPartOffsets[i].x / 20 * l, m * yValue}), PARTS_COLOUR);
                        }
                    }
                }
            default:
                break;
        }
    };

    void initPhase(const BOSS_2_PHASES _newPhase)
    {
        stepsElapsed = -1;
        switch (_newPhase)
        {
        case PHASE_1:
            {
                movementVector.x = -0.4f;
                automaton1->SetPhase(Boss2Automaton::PHASE_1_AUTOMATON_1);
                automaton2->SetPhase(Boss2Automaton::PHASE_1_AUTOMATON_2);
            }
            break;
        case PRE_FIGHT:
            movementVector = Vector2Zeros;
            automaton1->SetPhase(Boss2Automaton::PRE_FIGHT);
            automaton2->SetPhase(Boss2Automaton::PRE_FIGHT);
            break;
        case PHASE_2:
            currentSmallPart = 0;
            movementVector.x = 0.4f;
            movementVector.y = -0.5f;

            automaton1->SetPhase(Boss2Automaton::PHASE_2_AUTOMATON_1);
            automaton2->SetPhase(Boss2Automaton::PHASE_2_AUTOMATON_2);
            break;
        case PRE_PHASE_3:
            movementVector = Vector2Zeros;
            automaton1->SetPhase(Boss2Automaton::PRE_PHASE_3_AUTOMATON_1);
            automaton2->SetPhase(Boss2Automaton::PRE_PHASE_3_AUTOMATON_2);
                break;
        case PHASE_3:
            movementVector.x = 0.02f;
            automaton1->SetPhase(Boss2Automaton::PHASE_3);
            automaton2->SetPhase(Boss2Automaton::PHASE_3);
            break;
        case PHASE_4:
            if (position.x > 60)
                movementVector.x = -0.3f;
            else if (position.x < 60)
                movementVector.x = 0.3f;
            break;
        case PHASE_DEFEAT:
            {
                currentSmallPart = 0;
                SoundHandler::StopSound(HUM_1);
                constexpr int halfOfShotNum = 15;
                const Vector2 spawnPos = {position.x, position.y + 15};
                for (int i = -halfOfShotNum; i <= halfOfShotNum; i++)
                {
                    //Vector2 direction = Vector2Rotate(Vector2(1, 0), PI/static_cast<float>(i));
                    const float j = i;
                    const Vector2 direction = Vector2Rotate(Vector2Normalize(Vector2(j / halfOfShotNum, -0.5f - j / halfOfShotNum)), 0.75f);
                    simpleBullet1SlowPool->spawn().spawn(spawnPos, direction, {255, 0, 0, 255});
                    simpleBullet1SlowPool->spawn().spawn(Vector2Add(spawnPos, direction * 10), direction, {200, 0, 0, 255});
                    simpleBullet1SlowPool->spawn().spawn(Vector2Add(spawnPos, direction * 20), direction, {145, 0, 0, 255});
                    //fireBurst(Vector2Add(position, direction), direction);
                }
            }
            break;
        }
    }

public:
    explicit Boss2(const int _health = 1)
    : Boss(500, {0, COLLIDER_Y_OFFSET, 58, 50}, _health)
    {

        crossBullet1Pool = std::make_shared<PoolingVector<Boss2CrossBullet1>>(100);
        automatonPinkBulletPool = std::make_shared<PoolingVector<Boss2AutomatonPinkBullet>>(300);;
        automatonVariableSpeedBulletPool = std::make_shared<PoolingVector<SimpleBullet2VariableSpeed>>(100);
        smallBulletPool = std::make_shared<PoolingVector<Boss2SmallBullet>>(500);
        simpleBullet1SlowPool = std::make_shared<PoolingVector<SimpleBullet1Slow>>(100);
        simpleBullet1FastPool = std::make_shared<PoolingVector<Boss1FastBurstBullet>>(150);
        GlobalPools::AddPools({smallBulletPool, simpleBullet1SlowPool, simpleBullet1FastPool, automatonPinkBulletPool, automatonVariableSpeedBulletPool, crossBullet1Pool});
        collider2 = {0, COLLIDER_2_Y_OFFSET, 30, 24};
        automaton1 = std::make_shared<Boss2Automaton>(automatonPinkBulletPool, automatonVariableSpeedBulletPool);
        automaton2 = std::make_shared<Boss2Automaton>(automatonPinkBulletPool, automatonVariableSpeedBulletPool);
        automaton1->spawn(Vector2{-10, 15});
        automaton2->spawn(Vector2{130, 15});
        SpawnedEnemies::spawnEnemy(automaton1);
        SpawnedEnemies::spawnEnemy(automaton2);
    }

    void doPreStep() override
    {
        stepsElapsed++;
    }

    bool doPhysics() override
    {
        const Vector2 _scrollVector = BackgroundHandler::GetScrollVector();
        position -= _scrollVector;
        if (position.x > 60 + maxMovement || position.x < 60 - maxMovement)
            movementVector.x *= -1;
        position += movementVector;
        collider.x = position.x - (collider.width / 2);
        collider.y = position.y - (collider.height / 2) + COLLIDER_Y_OFFSET;
        collider2.x = position.x - (collider2.width / 2);
        collider2.y = position.y - (collider2.height / 2) + COLLIDER_2_Y_OFFSET;
        switch (bossPhase)
        {
        case PRE_FIGHT:
            return true;
        case PHASE_1:
            {
                if (stepsElapsed % PHASE_1_FIRE_RATE == 0)
                {
                    if (++currentSmallPart >= 30)
                        currentSmallPart = 0;
                    else if (currentSmallPart == 1)
                        SoundHandler::PlaySound(SOUNDS::BANG_2);
                    float _extraRotation = 0;
                    if (currentSmallPart == 0 || currentSmallPart == 7 || currentSmallPart == 12 || currentSmallPart == 18)
                        _extraRotation = 0.2f;
                    else if (currentSmallPart == 3 || currentSmallPart == 11 || currentSmallPart == 15)
                        _extraRotation = -0.2f;
                    if (currentSmallPart < 20)
                        fireSmallPartShot(currentSmallPart % 10, 2, _extraRotation);
                    //fireSmallPartShot(currentSmallPart, 0.75f + static_cast<float>(static_cast<int>(stepsElapsed) % 240 - 120) / 1000, static_cast<float>(static_cast<int>(stepsElapsed) % 240 - 120) / 5000);
                }
                break;
            }
        case PHASE_2:
            {
                if (stepsElapsed % PHASE_2_FIRE_RATE == 0)
                {
                    if (currentSmallPart-- == 0)
                        currentSmallPart = 9;
                    float _maxRotation = 1;
                    fireSmallPartShot(currentSmallPart, _maxRotation);
                    fireSmallPartShot(9 - currentSmallPart, _maxRotation);
                }

                if (position.y < 39.4f)
                {
                    movementVector.y = 0;
                    position.y = 39.5f;
                } else if (position.y > 60.5f)
                {
                    if (position.y < 62)
                    {
                        movementVector.y = 0;
                        position.y = 60;
                    }
                }
                else if (position.x <= 40 || position.x >= 80)
                {
                    movementVector.y = 0.5f;
                } else if (position.x > 40 && position.x < 80)
                {
                    movementVector.y = -0.5f;
                } else
                {
                    movementVector.y = 0.0f;
                }

                if (stepsElapsed % 60 == 0 || stepsElapsed % 60 == 3)
                {
                    for (int i = 0; i < 4; i++)
                        firePhase2CrossShot(i);
                }
            }
            break;
        case PRE_PHASE_3:
            position = Vector2MoveTowards(position, BackgroundHandler::GetRelativePos(Vector2(60, -1900)), 0.5f);
            break;
        case PHASE_3:
                if (position.x >= 62 || position.x <= 58)
                    movementVector.x = -movementVector.x;
            if (stepsElapsed % PHASE_3_FIRE_RATE == 0)
            {
                firePhase3SmallPartShot(LOW);
            } else if (stepsElapsed % PHASE_3_FIRE_RATE == 21)
                firePhase3SmallPartShot(MIDDLE);
            else if (stepsElapsed % PHASE_3_FIRE_RATE == 42)
                firePhase3SmallPartShot(HIGH);
            break;
        case PHASE_4:
            {
                SoundHandler::PlaySound(HUM_1, true);
                if (abs(position.x - 60) < 0.5f)
                {
                    position.x = 60;
                    movementVector.x = 0;
                }
                if (stepsElapsed % PHASE_4_FIRE_RATE == 0)
                {
                    smallPartsGlowSteps = 24;
                    for (int i = 0; i < 10; i++)
                        fireSmallPartShot(i, 0);
                }
                if (stepsElapsed % 80 <= 3)
                {
                    Vector2 _pos = {position.x - 15, position.y + 7.5f};
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    if (stepsElapsed % 80 == 0)
                    {
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                        _pos.x = position.x + 15;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    } else if (stepsElapsed % 80 == 3)
                    {
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                        _pos.x = position.x + 15;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    }
                }
                if (stepsElapsed % 140 == 0)
                {
                    Vector2 _pos = {position.x - 20.1f, position.y - 14.8f};
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}), true);
                } else if (stepsElapsed % 140 == 50)
                {Vector2 _pos = {position.x + 20.1f, position.y - 14.8f};
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}), true);
                }
            }
            break;
        }
        checkPlayerCollision();
        checkPlayerCollision(collider2);
        if (checkPlayerBulletCollision())
            takeDamage();
        if (checkPlayerBulletCollision(collider2))
            takeDamage();
        return true;
    }

    void doPostStep()
    {
        drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 45)
            drawnColour = RED;
        const SpriteParametres opts = {.i=BOSS_2_RING, .pos=position, .yOffset=baseSpriteYOffset, .l = LAYER_GROUNDED, .col = drawnColour};
        SpriteHandler::QueueMyAnimatedSprite(opts);
        SpriteHandler::QueueMyStaticSprite({.i=BOSS_2_BASE, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour});
        for (int i = 0; i < currentSmallPartsGlowSteps.size(); i++)
        {
            int j = --currentSmallPartsGlowSteps[i];
            if (j > 0)
                SpriteHandler::QueueMyStaticSprite({.i=BOSS_2_SMALL_PART_GLOW, .pos = Vector2Add(position, smallPartOffsets[i]), .l = LAYER_GROUNDED});
        }

        for (int i = 0; i < currentCrossGlowSteps.size(); i++)
        {
            int j = --currentCrossGlowSteps[i];
            if (j > 0)
                SpriteHandler::QueueMyStaticSprite({.i=BOSS_2_CROSS_GLOW, .pos = Vector2Add(position, crossOffsets[i]), .l = LAYER_GROUNDED, .col = drawnColour});
        }
    }


    void SetPhase(const BOSS_2_PHASES _newPhase)
    {
        bossPhase = _newPhase;
        initPhase(_newPhase);
    }
    void SetSpriteDamage(const uint_fast8_t _damage)
    {
        baseSpriteYOffset = _damage;
    }
};
#endif //RAYLIB_STG_BOSS2_H
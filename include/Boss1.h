//
// Created by n on 08/08/2026.
//

#ifndef RAYLIB_STG_BOSS1_H
#define RAYLIB_STG_BOSS1_H
#include "Boss.h"
#include "Boss1SmallBullet.h"
#include "Boss1FastBurstBullet.h"
#include "SimpleBullet1Slow.h"
#include "SimpleBullet2.h"

class Boss1 : public Boss
{
public:
    constexpr static int COLLIDER_Y_OFFSET = -14;
    constexpr static int maxMovement = 15; //How far, in one direction on the X-axis, may the boss move?
    constexpr static Color PARTS_COLOUR = {223, 113, 38, 255};
    constexpr static Color SPREAD_COLOUR = {250, 150, 60, 255};
    constexpr static uint8_t PHASE_1_FIRE_RATE = 4;
    constexpr static uint8_t PHASE_2_FIRE_RATE = 8;
    constexpr static uint8_t PHASE_3_FIRE_RATE = 76;
    constexpr static uint8_t PHASE_4_FIRE_RATE = 24;
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1,
        PHASE_2,
        PHASE_3,
        PHASE_4,
        PHASE_DEFEAT
    }BOSS_1_PHASES;
private:
    std::shared_ptr<PoolingVector<Boss1SmallBullet>> boss1SmallBullets;
    std::shared_ptr<PoolingVector<SimpleBullet1Slow>> simpleBullet1SlowPool;
    std::shared_ptr<PoolingVector<Boss1FastBurstBullet>> simpleBullet1FastPool;
    BOSS_1_PHASES bossPhase = PRE_FIGHT;
    static constexpr std::array<Vector2, 11> smallPartOffsets = {
        Vector2(-38.0784, 7.98439),
        Vector2(-34.6784, 13.0844),
        Vector2(-30.4284, 18.1844),
        Vector2(-20.2284, 21.5844),
        Vector2(-11.7284, 20.7344),
        Vector2(0, 20.7344),
        Vector2(11.7284, 20.7344),
        Vector2(20.2284, 21.5844),
        Vector2(30.4284, 18.1844),
        Vector2(34.6784, 13.0844),
        Vector2(38.0784, 7.98439),
    };
    uint stepsElapsed = 0;
    uint8_t currentSmallPart = 0;
    int part1GlowSteps = 0;
    int part2GlowSteps = 0;
    int part3GlowSteps = 0;
    int part4GlowSteps = 0;
    int smallPartsGlowSteps = 0;
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
            simpleBullet1SlowPool->spawn().spawn(translatedPos, rotatedDir, SPREAD_COLOUR);
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
                simpleBullet1SlowPool->spawn().spawn(translatedPos, rotatedDir, SPREAD_COLOUR);
            else
                simpleBullet1FastPool->spawn().spawn(translatedPos, rotatedDir, RED);
        }
    }

    void fireSmallPartShot(uint8_t _currentSmallPart = 12, const float _maxRotation = 0.75f, const float _extraRotation = 0) const
    {
        if (_currentSmallPart == 12)
            _currentSmallPart = currentSmallPart;
        const Vector2 playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
        const Vector2 _startingDirection = Vector2Normalize(smallPartOffsets[_currentSmallPart]);
        const Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[_currentSmallPart]);
        const Vector2 _vectorToPlayer = Vector2Subtract(playerPos, _currentBulletSpawnPos);
        const float _rotation = std::clamp(Vector2Angle(_startingDirection, _vectorToPlayer) + _extraRotation, -_maxRotation, _maxRotation);
        boss1SmallBullets->spawn().spawn(_currentBulletSpawnPos, Vector2Rotate(_startingDirection, _rotation), PARTS_COLOUR);
    }

    void initPhase(const BOSS_1_PHASES _newPhase)
    {
        switch (_newPhase)
        {
        case PHASE_1:
            {
                //movementVector.x = -0.2f;
            }
            break;
        case PRE_FIGHT:
            movementVector.x = 0;
            break;
        case PHASE_2:
            movementVector.x = 0.2f;
            break;
        case PHASE_3:
            movementVector.x = -0.1f;
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
                smallPartsGlowSteps = 0;
                part1GlowSteps = 0;
                part2GlowSteps = 0;
                part3GlowSteps = 0;
                part4GlowSteps = 0;
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
    explicit Boss1(std::shared_ptr<PoolingVector<Boss1SmallBullet>> _boss1SmallBulletPool, std::shared_ptr<PoolingVector<SimpleBullet1Slow>> _simpleBullet1SlowPool, std::shared_ptr<PoolingVector<Boss1FastBurstBullet>> _simpleBullet1FastPool, const int _health = 1)
    : Boss(500, {0, COLLIDER_Y_OFFSET, 80, 45}, _health)
    {
        boss1SmallBullets = _boss1SmallBulletPool;
        simpleBullet1SlowPool = _simpleBullet1SlowPool;
        simpleBullet1FastPool = _simpleBullet1FastPool;
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
        switch (bossPhase)
        {
        case PRE_FIGHT:
            return true;
        case PHASE_1:
            {
                if (stepsElapsed % 40 == 0)
                {
                    Vector2 _pos = {position.x - 20.1f, position.y - 14.8f};
                    part1GlowSteps = 20;
                    part4GlowSteps = 20;
                    const Vector2 _leftCorner = {position.x - 60, position.y - 28.5f};
                    fireSpread(_pos, Vector2Normalize({_leftCorner.x - _pos.x, _leftCorner.y - _pos.y + 3}));
                    _pos.x = position.x + 20.1f;
                    const Vector2 _rightCorner = {position.x + 60, position.y - 28.5f};
                    fireSpread(_pos, Vector2Normalize({_rightCorner.x - _pos.x, _rightCorner.y - _pos.y + 3}));
                }
                if (stepsElapsed % PHASE_1_FIRE_RATE == 0)
                {
                    if (++currentSmallPart >= 11)
                        currentSmallPart = 0;
                    fireSmallPartShot(currentSmallPart, 0.75f + static_cast<float>(static_cast<int>(stepsElapsed) % 240 - 120) / 1000, static_cast<float>(static_cast<int>(stepsElapsed) % 240 - 120) / 5000);
                }
                break;
            }
        case PHASE_2:
            {
                if (stepsElapsed % PHASE_2_FIRE_RATE == 0)
                {
                    if (currentSmallPart-- == 0)
                        currentSmallPart = 10;
                    fireSmallPartShot(currentSmallPart);
                }

                if (stepsElapsed % 60 == 0)
                {
                    Vector2 _pos = {position.x - 20.1f, position.y - 14.8f};
                    part1GlowSteps = 20;
                    part4GlowSteps = 20;
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    _pos.x = position.x + 20.1f;
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                }
            }
            break;
        case PHASE_3:
            {
                if (stepsElapsed % PHASE_3_FIRE_RATE == 0)
                {
                    smallPartsGlowSteps = 24;
                    for (int i = 0; i < 10; i++)
                        fireSmallPartShot(i, 1);
                }
                if (stepsElapsed % 60 == 0)
                {
                    Vector2 _pos = {position.x - 20.1f, position.y - 14.8f};
                    part1GlowSteps = 20;
                    part4GlowSteps = 20;
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    _pos.x = position.x + 20.1f;
                    fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                }
            }
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
                        part2GlowSteps = 20;
                        part3GlowSteps = 20;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                        _pos.x = position.x + 15;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    } else if (stepsElapsed % 80 == 3)
                    {
                        part2GlowSteps = 20;
                        part3GlowSteps = 20;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                        _pos.x = position.x + 15;
                        fireSpread(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                    }
                }
                if (stepsElapsed % 140 == 0)
                {
                    Vector2 _pos = {position.x - 20.1f, position.y - 14.8f};
                    part1GlowSteps = 20;
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}), true);
                } else if (stepsElapsed % 140 == 50)
                {Vector2 _pos = {position.x + 20.1f, position.y - 14.8f};
                    part4GlowSteps = 20;
                    const Vector2 _playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}), true);
                }
            }
            break;
        }
        checkPlayerCollision();
        if (checkPlayerBulletCollision())
            takeDamage();
        return true;
    }

    void doPostStep()
    {
        drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 45)
            drawnColour = RED;
        const SpriteParametres opts = {.i=BOSS_1_BASE, .pos=position, .yOffset=baseSpriteYOffset, .l = LAYER_GROUNDED, .col = drawnColour};
        SpriteHandler::QueueMyStaticSprite(opts);
        if (part1GlowSteps-- > 0)
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_1, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        if (part2GlowSteps-- > 0)
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_2, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        if (part3GlowSteps-- > 0)
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_3, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        if (part4GlowSteps-- > 0)
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_4, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        if (smallPartsGlowSteps-- > 0)
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_SMALL_PARTS, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 57, 92, 57}});
        switch (bossPhase)
        {
        case PRE_FIGHT:
            break;
        case PHASE_1:
                {
                const auto xOffset = static_cast<float>(stepsElapsed / PHASE_1_FIRE_RATE % 11 * 92);
                    const SpriteParametres smallPartsOpts = {.i=BOSS_1_SMALL_PARTS, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={xOffset, 0, 92, 57}};
                    SpriteHandler::QueueMyStaticSprite(smallPartsOpts);
                    break;
                }
        case PHASE_2:
            {
                const auto xOffset = static_cast<float>(1012 - stepsElapsed / PHASE_2_FIRE_RATE % 11 * 92);
                const SpriteParametres smallPartsOpts = {.i=BOSS_1_SMALL_PARTS, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={xOffset, 0, 92, 57}};
                SpriteHandler::QueueMyStaticSprite(smallPartsOpts);
                break;
            }
        case PHASE_3:
            break;
        }
    }


    void SetPhase(const BOSS_1_PHASES _newPhase)
    {
        bossPhase = _newPhase;
        initPhase(_newPhase);
    }
    void SetSpriteDamage(const uint_fast8_t _damage)
    {
        baseSpriteYOffset = _damage;
    }
};
#endif //RAYLIB_STG_BOSS1_H
//
// Created by n on 08/08/2026.
//

#ifndef RAYLIB_STG_BOSS1_H
#define RAYLIB_STG_BOSS1_H
#include "Boss.h"
#include "Boss1SmallBullet.h"
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
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1,
        PHASE_2,
        PHASE_3,
    }BOSS_1_PHASES;
private:
    std::shared_ptr<PoolingVector<Boss1SmallBullet>> boss1SmallBullets;
    std::shared_ptr<PoolingVector<SimpleBullet1>> simpleBullet1Pool;
    BOSS_1_PHASES bossPhase = PRE_FIGHT;
    std::array<Vector2, 11> smallPartOffsets = {
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
    int part4GlowSteps = 0;
    Color drawnColour = WHITE;
    Vector2 movementVector = {};

    void fireSpread(const Vector2 _pos, const Vector2 _dir)
    {
        for (int i = -3; i < 3; i++)
        {
            const Vector2 translatedPos = Vector2Add(_pos, {-_dir.y * i * 3, _dir.x * i * 3});
            const Vector2 rotatedDir = Vector2Rotate(_dir, i * 0.2f);
            simpleBullet1Pool->spawn().spawn(translatedPos, rotatedDir, SPREAD_COLOUR);
        }
    }

    void fireBurst(const Vector2 _pos, const Vector2 _dir)
    {
        for (int i = -3; i < 3; i++)
        {
            const Vector2 translatedPos = Vector2Add(_pos, {-_dir.y * i + i * i, _dir.x * i * 1.5f - i * i});
            const Vector2 rotatedDir = Vector2Rotate(_dir, i * i * 0.02f);
            simpleBullet1Pool->spawn().spawn(translatedPos, rotatedDir, SPREAD_COLOUR);
        }
    }

    void fireSmallPartShot(uint8_t _currentSmallPart, float _maxRotation = 0.75f)
        {
        Vector2 playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
        const Vector2 _startingDirection = Vector2Normalize(smallPartOffsets[currentSmallPart]);
        const Vector2 _currentBulletSpawnPos = Vector2Add(position, smallPartOffsets[currentSmallPart]);
        const Vector2 _vectorToPlayer = Vector2Subtract(playerPos, _currentBulletSpawnPos);
        const float _rotation = std::clamp(Vector2Angle(_startingDirection, _vectorToPlayer), -_maxRotation, _maxRotation);
        boss1SmallBullets->spawn().spawn(_currentBulletSpawnPos, Vector2Rotate(_startingDirection, _rotation), PARTS_COLOUR);
    }

    void initPhase(const BOSS_1_PHASES _newPhase)
    {
        switch (_newPhase)
        {
        case PHASE_1:
            {
                movementVector.x = -0.2f;
            }
            break;
        case PRE_FIGHT:
            movementVector.x = 0;
            break;
        case PHASE_2:
            movementVector.x = 0.2f;
            break;
        default:
            break;
        }
    }

public:
    explicit Boss1(std::shared_ptr<PoolingVector<Boss1SmallBullet>> _boss1SmallBulletPool, std::shared_ptr<PoolingVector<SimpleBullet1>> _simpleBullet1Pool, const int _health = 1)
    : Boss(500, {0, COLLIDER_Y_OFFSET, 80, 45}, _health)
    {
        boss1SmallBullets = _boss1SmallBulletPool;
        simpleBullet1Pool = _simpleBullet1Pool;
    }

    void doPreStep() override
    {
        stepsElapsed++;
        drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 30)
            drawnColour = RED;
        const SpriteParametres opts = {.i=BOSS_1_BASE, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour};
        SpriteHandler::QueueMyStaticSprite(opts);
        if (part1GlowSteps-- > 0)
        {
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_1, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        }
        if (part4GlowSteps-- > 0)
        {
            SpriteHandler::QueueMyStaticSprite({.i=BOSS_1_PART_4, .pos=position, .l = LAYER_GROUNDED, .col = drawnColour, .rect={0, 0, 92, 57}});
        }
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
        default:
            break;
        }
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
                    _pos.x = 120- _pos.x;
                    const Vector2 _rightCorner = {position.x + 60, position.y - 28.5f};
                    fireSpread(_pos, Vector2Normalize({_rightCorner.x - _pos.x, _rightCorner.y - _pos.y + 3}));
                }
                if (stepsElapsed % PHASE_1_FIRE_RATE == 0)
                {
                    if (++currentSmallPart >= 11)
                        currentSmallPart = 0;
                    fireSmallPartShot(currentSmallPart);
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
                    _pos.x = 120- _pos.x;
                    const Vector2 _rightCorner = {position.x + 60, position.y - 28.5f};
                    fireBurst(_pos, Vector2Normalize({_playerPos.x - _pos.x, _playerPos.y - _pos.y + 3}));
                }
            }
            break;
        default:
            break;
        }
        checkPlayerCollision();
        if (checkPlayerBulletCollision())
            takeDamage();
        return true;
    }


    void SetPhase(const BOSS_1_PHASES _newPhase)
    {
        bossPhase = _newPhase;
        initPhase(_newPhase);
    }
};
#endif //RAYLIB_STG_BOSS1_H
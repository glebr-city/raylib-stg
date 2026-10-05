//
// Created by n on 28/09/2026.
//

#ifndef RAYLIB_STG_BOSS2AUTOMATON_H
#define RAYLIB_STG_BOSS2AUTOMATON_H
#include "Boss2AutomatonPinkBullet.h"
#include "RNGHandler.h"
#include "SimpleBullet2VariableSpeed.h"

struct Boss2AutomatonState //Based heavily on Enemy1State.
{
    Vector2 desiredPos = {};
    float speed = 0; // Movement speed, units per second.
    u_int duration = 0; // State will end after this many ticks if > 0 .
    u_int fireRate = 0; // No. of ticks between shots; 0 to not shoot.
    bool despawn = false; // Despawn after completing this state?
    bool slowAtDesiredPos = true; //Should the enemy slow down between states?
};

class Boss2Automaton : public Enemy //Copying Enemy1Base... perhaps not the best idea, but we shall see.
{
private:
    const u_int PHASE_1_FIRE_RATE = 30;
    const u_int PHASE_2_FIRE_RATE = 100;
    bool isDisabled = false;
public:
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1_AUTOMATON_1,
        PHASE_1_AUTOMATON_2,
        PHASE_2_AUTOMATON_1,
        PHASE_2_AUTOMATON_2,
        PHASE_2,
        PHASE_3,
        PHASE_4,
        PHASE_DEFEAT
    }BOSS_2_AUTOMATON_PHASES;
private:
    const std::vector<std::vector<Boss2AutomatonState>> phaseVectors{
        std::vector<Boss2AutomatonState>{{}},
        std::vector<Boss2AutomatonState>{{.desiredPos = {60, 5}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {120, 15}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {60, 25}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {0, 15}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}},
        std::vector<Boss2AutomatonState>{{.desiredPos = {60, 25}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {0, 15}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {60, 5}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {120, 15}, .speed = 50, .fireRate = PHASE_1_FIRE_RATE, .slowAtDesiredPos = false}},
        std::vector<Boss2AutomatonState>{{.desiredPos = {60, 5}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {117, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {120, 40}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = true}, {.desiredPos = {117, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {60, 25}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {3, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {0, 40}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = true}, {.desiredPos = {3, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}},
        std::vector<Boss2AutomatonState>{{.desiredPos = {60, 25}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {3, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {0, 40}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = true}, {.desiredPos = {3, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {60, 5}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {117, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}, {.desiredPos = {120, 40}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = true}, {.desiredPos = {117, 15}, .speed = 50, .fireRate = PHASE_2_FIRE_RATE, .slowAtDesiredPos = false}},
    };

    const std::vector<int> phaseHealth{
        0,
        20,
        20,
        20,
        20,
    };

protected:
    static constexpr ANIMATED_SPRITES sprite = BOSS_2_AUTOMATON;
    BOSS_2_AUTOMATON_PHASES currentPhase = PRE_FIGHT;
    std::shared_ptr<PoolingVector<Boss2AutomatonPinkBullet>> pinkBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet2VariableSpeed>> variableSpeedBulletPool;
    u_int elapsedSteps;
    std::vector<Boss2AutomatonState> stateVector = {{.speed = 0}};
    u_int currentStateIndex = 0;
    float currentSpeed = 0;
    u_int elapsedStepsInState = 0;
    bool hasStartedSlowing = false;

    virtual void shootPinkRandomBullets()
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        Vector2 pinkBulletDirection = Vector2Normalize(Vector2Subtract({playerFinalPos.x, playerFinalPos.y}, position));
        RNGHandler::StepSeed();
        pinkBulletDirection = Vector2Rotate(pinkBulletDirection, (static_cast<float>(static_cast<int>(RNGHandler::GetSeed() % 31) - 15)) / 50);
        pinkBulletPool->spawn().spawn(position, pinkBulletDirection, PINK);
    }

    virtual void shootVariableSpeedBullet(const float _speed, const float _rotation = 0, Color _col = PINK)
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        const Vector2 pinkBulletDirection = Vector2Rotate(Vector2Normalize(Vector2Subtract({playerFinalPos.x, playerFinalPos.y}, position)), _rotation);
        //RNGHandler::StepSeed();
        //pinkBulletDirection = Vector2Rotate(pinkBulletDirection, (static_cast<float>(static_cast<int>(RNGHandler::GetSeed() % 31) - 15)) / 50);
        variableSpeedBulletPool->spawn().spawn(_speed, position, pinkBulletDirection, _col);
    }



    void initPhase(const BOSS_2_AUTOMATON_PHASES _newPhase)
    {
        SetHealth(phaseHealth[_newPhase]);
        switch (_newPhase)
        {
        case PRE_FIGHT:
            isDisabled = true;
            stateVector = phaseVectors[PRE_FIGHT];
            break;
        case PHASE_1_AUTOMATON_1:
            position = {-10, 15};
            stateVector = phaseVectors[PHASE_1_AUTOMATON_1];
            isDisabled = false;
            break;
        case PHASE_1_AUTOMATON_2:
            position = {130, 15};
            stateVector = phaseVectors[PHASE_1_AUTOMATON_2];
            isDisabled = false;
            break;
        case PHASE_2_AUTOMATON_1:
            stateVector = phaseVectors[PHASE_2_AUTOMATON_1];
            isDisabled = false;
            break;
        case PHASE_2_AUTOMATON_2:
            stateVector = phaseVectors[PHASE_2_AUTOMATON_2];
            isDisabled = false;
            break;
        default:
            break;
        }
        currentStateIndex = 0;
        enterNewState(0);
    }

    virtual void handleShooting()
    {
        const auto _currentState = stateVector[currentStateIndex];
            switch (currentPhase)
            {
            case PRE_FIGHT:
                return;
            case PHASE_1_AUTOMATON_1:
            case PHASE_1_AUTOMATON_2:
                if (elapsedSteps % _currentState.fireRate == 0)
                {
                    SoundHandler::PlaySound(THUMP_1);
                    shootPinkRandomBullets();
                    shootPinkRandomBullets();
                }
                return;
            case PHASE_2_AUTOMATON_1:
            case PHASE_2_AUTOMATON_2:
                const float movementDirection = -std::copysignf( 0.2f, Vector2Subtract(stateVector[currentStateIndex].desiredPos, position).x);
                const auto stepThing = elapsedSteps % _currentState.fireRate;
                const Color bulletColour = { static_cast<u_char>(255 - stepThing * 3), static_cast<u_char>(109 - stepThing * 3), static_cast<u_char>(194 - stepThing * 3), 255 };
                if (stepThing == 0)
                {
                    shootVariableSpeedBullet(0.8f, 0, bulletColour);
                } else if (stepThing == 6)
                {
                    shootVariableSpeedBullet(0.9f, 0.1f * movementDirection, bulletColour);
                } else if (stepThing == 13)
                {
                    shootVariableSpeedBullet(1.0f, 0.2f * movementDirection, bulletColour);
                } else if (stepThing == 16)
                {
                    shootVariableSpeedBullet(1.1f, 0.3f * movementDirection, bulletColour);
                } else if (stepThing == 19)
                {
                    shootVariableSpeedBullet(1.2f, 0.4f * movementDirection, bulletColour);
                } else if (stepThing == 22)
                {
                    shootVariableSpeedBullet(1.3f, 0.5f * movementDirection, bulletColour);
                } else if (stepThing == 25)
                {
                    shootVariableSpeedBullet(1.4f, 0.4f * movementDirection, bulletColour);
                }else if (stepThing == 28)
                {
                    shootVariableSpeedBullet(1.5f, 0.3f * movementDirection, bulletColour);
                } else if (stepThing == 31)
                {
                    shootVariableSpeedBullet(1.6f, 0, bulletColour);
                }
                break;
            //default:
                //return;
            }
        return;
        }

public:

    Boss2Automaton(const std::shared_ptr<PoolingVector<Boss2AutomatonPinkBullet>>& _pinkBulletPool, const std::shared_ptr<PoolingVector<SimpleBullet2VariableSpeed>>& _variableSpeedPool, const uint _scoreValue = 2000) : Enemy(_scoreValue) {
        pinkBulletPool = _pinkBulletPool;
        variableSpeedBulletPool = _variableSpeedPool;
        elapsedSteps = -1;
        position = {0, 0};
        collider = {0, 0, 10, 10};
        stateVector = {{}};
        Boss2Automaton::enterNewState(0);
    }

    void doPostStep() override
    {
        if (isDisabled)
        {
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 2, .l = LAYER_ENEMY, .col=WHITE});
            return;
        }
        auto drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 40 > 25)
            drawnColour = RED;
        int yOffset = 0;
        if (stateVector[currentStateIndex].fireRate > 0 && elapsedSteps % stateVector[currentStateIndex].fireRate < 10)
            yOffset = 1;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = yOffset, .l = LAYER_ENEMY, .col=drawnColour});
    }

    bool doPhysics() override
    {
        elapsedSteps++;
        if (!isDisabled)
        {
            checkPlayerCollision();
            handleShooting();
            if (checkPlayerBulletCollision())
            {
                if (!takeDamage())
                {
                    SoundHandler::PlaySound(EXPLOSION_2);
                    ScoreHandler::addScore(3000, true);
                    isDisabled = true;
                }
            }
        }
        const Boss2AutomatonState currentState = stateVector[currentStateIndex];
        if (++elapsedStepsInState == currentState.duration)
            return enterNewState(currentStateIndex + 1);
        if (currentState.slowAtDesiredPos)
        {
            if (Vector2DistanceSqr(position, currentState.desiredPos) < (currentState.speed / 4) * (currentState.speed / 4))
            {
                if (!hasStartedSlowing)
                {
                    hasStartedSlowing = true;
                    currentSpeed = currentState.speed;
                }
                currentSpeed = std::clamp(currentSpeed - currentState.speed / 60, 0.0f, currentState.speed);
                if (currentSpeed == 0.0f) //Done moving, now enter the new state!
                {
                    position = currentState.desiredPos;
                    return enterNewState(currentStateIndex + 1);
                }
            }
            else if (currentSpeed < currentState.speed)
                currentSpeed = currentSpeed + currentState.speed / 60;
        } else
        {
            if (currentSpeed < currentState.speed)
                currentSpeed = std::clamp(currentSpeed + currentState.speed / 60, 0.0f, currentState.speed);
            else if (currentSpeed > currentState.speed)
                currentSpeed = std::clamp(currentSpeed - currentState.speed / 60, 0.0f, currentState.speed);
            if (Vector2DistanceSqr(position, currentState.desiredPos) <= (currentState.speed / 120) * (currentState.speed / 120))
            {
                position = currentState.desiredPos;
                return enterNewState(currentStateIndex + 1);
            }
        }
        position = Vector2MoveTowards(position, currentState.desiredPos, currentSpeed / 120);
        collider.x = position.x - collider.width / 2;
        collider.y = position.y - collider.height / 2;
        return true;
    }

    virtual bool enterNewState(const u_int newStateIndex)
    {
        hasStartedSlowing = false;
        if (stateVector[currentStateIndex].despawn)
            return false;
        if (stateVector[currentStateIndex].slowAtDesiredPos)
            currentSpeed = 0;
        elapsedStepsInState = 0;
        if (newStateIndex < stateVector.size())
            currentStateIndex = newStateIndex;
        else
            currentStateIndex = 0;
        return true;
    }

    void SetPhase(const BOSS_2_AUTOMATON_PHASES _newPhase)
    {
        currentPhase = _newPhase;
        initPhase(_newPhase);
    }

    void SetHealth(const int _health)
    {
        health = _health;
    }
};
#endif //RAYLIB_STG_BOSS2AUTOMATON_H
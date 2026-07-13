//
// Created by n on 12/07/2026.
//

#ifndef RAYLIB_STG_DIAGONALTANKPHASE1_H
#define RAYLIB_STG_DIAGONALTANKPHASE1_H
#include "DiagonalTank.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"

class DiagonalTankPhase1 : public PhaseHelper
{
private:
    u_int stepsElapsed{};
    std::shared_ptr<PoolingVector<SimpleBullet2>> diagonalTankBulletPool;
public:
    DiagonalTankPhase1() : PhaseHelper(std::vector<std::shared_ptr<IPoolingVector>>())
    {
        phaseName = "Diagonal Tanks";
        background = DIAGONAL_TANK_BACKGROUND;
        diagonalTankBulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(55, 30);
        defaultScrollVector = Vector2(0, 0.2f);
        currentScrollVector = defaultScrollVector;
        phasePools.push_back(diagonalTankBulletPool);
    }
    bool doPhysics(Player* _player) override
    {
        if (stepsElapsed == 0)
        {
            for (int rowNumber = 0; rowNumber < 3; rowNumber++)
            {
                for (int i = 0; i < 8; i++)
                {
                    std::unique_ptr<DiagonalTank> newTank = std::make_unique<DiagonalTank>(diagonalTankBulletPool.get(), 360 + i * 8 + rowNumber * 24);
                    newTank->spawn(Vector2(i * 17 - 31, i * -17 + rowNumber * -21 + 17));
                    SpawnedEnemies::spawnEnemy(std::move(newTank));
                }
            }
        }
        stepsElapsed++;
        return PhaseHelper::doPhysics(_player);
    };
};
#endif //RAYLIB_STG_DIAGONALTANKPHASE1_H
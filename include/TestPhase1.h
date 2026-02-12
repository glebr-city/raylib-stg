//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_TESTPHASE1_H
#define RAYLIB_STG_TESTPHASE1_H
#include "PhaseHelper.h"
#include "PoolingVector.h"
#include "SimpleBullet1.h"
#include "SimpleBullet2.h"


class TestPhase1 : public PhaseHelper {
    private:
    std::vector<IPoolingVector *> phasePools;
    PoolingVector<SimpleBullet1> movingDarkPurplePool;
    PoolingVector<SimpleBullet1> darkPurplePool;
public:
    TestPhase1();
    bool doPhysics(Player *player) override;
};


#endif //RAYLIB_STG_TESTPHASE1_H
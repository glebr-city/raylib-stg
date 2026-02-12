//
// Created by g on 11/02/2026.
//


#include "PlayerBullets.h"
std::unique_ptr<PoolingVector<PlayerBullet>> PlayerBullets::playerBullets = std::make_unique<PoolingVector<PlayerBullet>>(50);

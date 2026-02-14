//
// Created by g on 14/02/2026.
//


#include "ScoreItemHandler.h"

#include "PoolingVector.h"
#include "ScoreItem.h"
PoolingVector<ScoreItem> ScoreItemHandler::scoreItemPool{10000};

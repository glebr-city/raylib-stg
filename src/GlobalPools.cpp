//
// Created by n on 04/08/2026.
//

#include "../include/GlobalPools.h"

#include <memory>
#include <vector>
class IPoolingVector;
std::vector<std::shared_ptr<IPoolingVector>> GlobalPools::pools = {};

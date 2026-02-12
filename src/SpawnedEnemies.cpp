#include "SpawnedEnemies.h"

#include "Enemy.h"
std::unique_ptr<std::vector<std::unique_ptr<Enemy>>> SpawnedEnemies::spawnedEnemies = std::make_unique<std::vector<std::unique_ptr<Enemy>>>();
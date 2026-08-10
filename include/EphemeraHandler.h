//
// Created by n on 10/08/2026.
//

#ifndef RAYLIB_STG_EPHEMERAHANDLER_H
#define RAYLIB_STG_EPHEMERAHANDLER_H
#include <memory>
#include <vector>

#include "Ephemera.h"

class EphemeraHandler
{
public:

    typedef enum
    {
        EXPLOSION_SMALL,

        EPHEMERA_COUNT
    }EPHEMERAE;
private:
    static std::vector<std::shared_ptr<Ephemera>> spawnedEphemerae;
public:

    static void doPreStep() {
        for (const auto& e: spawnedEphemerae) {
            e->doPreStep();
        }
    }

    static void doPhysics() {
        for (int e = 0; e < spawnedEphemerae.size();) {
            auto _ephemera = spawnedEphemerae.at(e);
            if (_ephemera->doPhysics()) {
                e++;
                continue;
            }
            spawnedEphemerae.erase(spawnedEphemerae.begin()+e);
        }
    }
    static void Spawn(const Vector2 _pos = {}, const EPHEMERAE _type = EXPLOSION_SMALL, const LAYERS _layer = LAYER_ENEMY)
    {
        std::unique_ptr<Ephemera> e;
        switch (_type)
        {
        case EXPLOSION_SMALL:
            {
                e = std::make_unique<ExplosionSmall>(_pos, _layer);
            }
            break;
        default:
            break;
        }
        spawnedEphemerae.emplace_back(std::move(e));
    };
};
#endif //RAYLIB_STG_EPHEMERAHANDLER_H
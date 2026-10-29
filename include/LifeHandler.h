//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_LIFEHANDLER_H
#define RAYLIB_STG_LIFEHANDLER_H


class LifeHandler {
private:
    static int currentLives;
    static constexpr int maxLives = 2;
    static constexpr int startingLives = 2;
public:
    static void resetLives() {
        currentLives = startingLives;
    }
    static int getCurrentLives() {
        return currentLives;
    }
    static bool canSpawnPlayer() {
        if (currentLives <= 0)
            return false;
        currentLives--;
        return true;
    }
};
#endif //RAYLIB_STG_LIFEHANDLER_H
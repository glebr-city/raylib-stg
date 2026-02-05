//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_CURRENTSTEP_H
#define RAYLIB_STG_CURRENTSTEP_H

inline int& currentStep() {
    static int currentStep = 0;
    return currentStep;
}

inline int& gameHeight() {
    static int gameHeight = 180;
    return gameHeight;
}

inline int& gameWidth() {
    static int gameWidth = 120;
    return gameWidth;
}


#endif //RAYLIB_STG_CURRENTSTEP_H
//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_PLAYER_H
#define RAYLIB_STG_PLAYER_H
#include <StepThinker.h>


class Player : public StepThinker{
    public:
    void PreStep() override;
};



#endif //RAYLIB_STG_PLAYER_H
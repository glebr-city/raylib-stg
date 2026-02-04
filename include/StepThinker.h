//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_STEPTHINKER_H
#define RAYLIB_STG_STEPTHINKER_H

class StepThinker {
public:
    virtual ~StepThinker() = default;

    virtual void PreStep();
};


#endif //RAYLIB_STG_STEPTHINKER_H
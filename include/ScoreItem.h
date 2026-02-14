//
// Created by g on 13/02/2026.
//

#ifndef RAYLIB_STG_SCOREITEM_H
#define RAYLIB_STG_SCOREITEM_H
#include "StepThinker.h"

enum VALUE {
    DARK_SMALL = 0,
    DARK_MEDIUM = 8,
    DARK_LARGE = 16,
    LIGHT_SMALL = 24,
    LIGHT_MEDIUM = 32,
    LIGHT_LARGE = 40
};

class ScoreItem : public Spawnable {
protected:
    Vector2 position{};
    VALUE value = DARK_SMALL;
    public:
    ScoreItem() {
        position = Vector2 {};
    }
    ScoreItem(const Vector2 _position) {
        position = _position;
    }
    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(SCORE_ITEM, value, position);
    }

    void spawn(const Vector2 _position) override {
        position = _position;
        value = DARK_SMALL;
    }

    void spawn(const Vector2 _position, const int _value) {
        position = _position;
        int divided = static_cast<int>(floor(static_cast<double>(_value) / 10));
        switch (divided) {
            case 2: value = LIGHT_MEDIUM;
            case 3: value = LIGHT_LARGE;
            default: value = DARK_SMALL;
        }
    }

};
#endif //RAYLIB_STG_SCOREITEM_H
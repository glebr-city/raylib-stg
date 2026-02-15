//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_POOLINGVECTOR_H
#define RAYLIB_STG_POOLINGVECTOR_H
#include <iostream>
#include <vector>
#include <array>

#include "ScoreItem.h"

class IPoolingVector {
public:
    virtual ~IPoolingVector() = default;
    virtual void doPreStep() = 0;
    virtual void doPhysics() = 0;
    virtual void doPhysics(std::array<Vector2, 2> playerPosAndMovement) = 0;
    [[nodiscard]] virtual int getVectorSize() const = 0;
    virtual int getNumActive() = 0;
    virtual void setNumActive(int i) = 0;
    virtual std::vector<Vector2> getActivePositions() = 0;
    virtual int getValue() = 0;
};
template<typename T>
class PoolingVector : public IPoolingVector{
    int scoreItemValue = 0; //For spawning score items... I don't know what the best way to handle this is!
    int num_active = 0;
    std::vector<T> vector;
    public:
    PoolingVector(T _template, int size){
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(_template);
        }
    }

    PoolingVector(T _template, int size, const int _scoreValue) {
        scoreItemValue = _scoreValue;
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(_template);
        }
    }

    PoolingVector(const int size) {
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(T());
        }
    }

    PoolingVector(const int size, const int _scoreValue) {
        scoreItemValue = _scoreValue;
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(T());
        }
    }

    std::vector<T>& getVector() {
        return vector;
    }

    int getVectorSize() const override{
        return vector.size();
    }

    std::vector<Vector2> getActivePositions() override {
        std::vector<Vector2> activePositions;
        for (int i = 0; i < getNumActive(); i++) {
            activePositions.emplace_back(vector.at(i).getPosition());
        }
        return activePositions;
    }

    int getValue() override {
        return scoreItemValue;
    }

    void doPreStep() override {
        for (int i = 0; i < num_active; i++) {
            vector.at(i).doPreStep();
        }
    }

    void doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        for (int i = 0; i < num_active;) {
            if (vector.at(i).doPhysics(playerPosAndMovement)) {
                i++;
                continue;
            }
            std::iter_swap(vector.begin() + i, vector.begin() + --num_active);
        }
    }
    void doPhysics() override {
        for (int i = 0; i < num_active;) {
            if (vector.at(i).doPhysics()) {
                i++;
                continue;
            }
            std::iter_swap(vector.begin() + i, vector.begin() + --num_active);
        }
    }

    T& spawn() {
        if (num_active >= vector.size()) {
            num_active = 0;
        }
        return vector.at(num_active++);
    }

    int getNumActive() override {
        return num_active;
    }

    void setNumActive(const int i) override {
        num_active = i;
    }

};

#endif //RAYLIB_STG_POOLINGVECTOR_H
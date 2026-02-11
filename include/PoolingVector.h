//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_POOLINGVECTOR_H
#define RAYLIB_STG_POOLINGVECTOR_H
#include <iostream>
#include <ostream>
#include <vector>

#include "StepThinker.h"

class IPoolingVector {
    int num_active = 0;
public:
    virtual ~IPoolingVector() = default;
    virtual void doPreStep() = 0;
    virtual void doPhysics(std::array<Vector2, 2> playerPosAndMovement) = 0;
    [[nodiscard]] virtual int getVectorSize() const = 0;
    virtual int getNumActive() = 0;
    virtual void setNumActive(int i) = 0;
};
template<typename T>
class PoolingVector : public IPoolingVector{
    int num_active = 0;
    std::vector<T> vector;
    public:
    PoolingVector(T _template, int size){
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(_template);
        }
    }

    PoolingVector(int size) {
        vector.resize(size);
        for (int i = 0; i < size; i++) {
            vector.emplace_back(T());
        }
    }

    std::vector<T>* getVector() {
        return &vector;
    }
    int getVectorSize() const override{
        return vector.size();
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
    void doPhysics() {
        for (int i = 0; i < num_active;) {
            if (vector.at(i).doPhysics()) {
                i++;
                continue;
            }
            std::iter_swap(vector.begin() + i, vector.begin() + --num_active);
        }
    }

    T* spawn() {
        //std::cout << "Bullets active: "<< num_active << std::endl;
        return &vector.at(num_active++);
    }

    int getNumActive() override {
        return num_active;
    }

    void setNumActive(const int i) override {
        num_active = i;
    }

};

#endif //RAYLIB_STG_POOLINGVECTOR_H
//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_POOLINGVECTOR_H
#define RAYLIB_STG_POOLINGVECTOR_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstddef>

#include "raylib/raylib.h"

class IPoolingVector {
public:
    virtual ~IPoolingVector() = default;
    virtual void doPreStep() = 0;
    virtual void doPhysics() = 0;
    virtual void doPostStep() = 0;
    [[nodiscard]] virtual int getVectorSize() const = 0;
    virtual int getNumActive() = 0;
    virtual void setNumActive(std::size_t i) = 0;
    virtual std::vector<Vector2> getActivePositions() = 0;
    virtual int getValue() = 0;
};
template<typename T>
class PoolingVector : public IPoolingVector{
    std::size_t scoreItemValue = 0UL; //For spawning score items... I don't know what the best way to handle this is!
    std::size_t num_active = 0UL;
    std::size_t spawnIndex = 0UL; //The index of the next object to spawn -- allows for looping through the vector.
    std::vector<T> storage;
    public:
        explicit PoolingVector(T _template, const std::size_t size, const int _scoreItemValue)
		{
		    if (_scoreItemValue < 0)
		        scoreItemValue = _template.GetScoreValue();
		    else
				scoreItemValue = _scoreItemValue;
		    for (int i = 0; i < size; i++) {
		        storage.emplace_back(_template);
		    }
		}
        PoolingVector() : PoolingVector({}, 0, -1) {}
        explicit PoolingVector(const std::size_t size, const int _scoreValue = -1) : PoolingVector({}, size, _scoreValue) {}


    std::vector<T>& getVector() {
        return storage;
    }

    [[nodiscard]] int getVectorSize() const final {
        return storage.size();
    }

    std::vector<Vector2> getActivePositions() final {
        std::vector<Vector2> activePositions;
        std::transform(
        storage.begin(), 
        storage.begin() + num_active,
        std::back_inserter(activePositions),
        [](T& elem) {
            return elem.GetPosition();
        }
    );
        return activePositions;
    }

    int getValue() final {
        return scoreItemValue;
    }

    void doPreStep() final {
				std::for_each(this->storage.begin(), this->storage.begin() + num_active, [](auto& elem){elem.doPreStep();});
    }

    void doPostStep() final
		{

		    std::for_each(this->storage.begin(), this->storage.begin() + num_active, [](auto& elem){elem.doPostStep();});
		}

		void doPhysics() final {
      auto i = 0UL;  
			while(i < num_active && num_active > 0) {
				if(storage.at(i).doPhysics()) {
					i++;
				} else {
					num_active--;
					std::swap(storage.at(i), storage.at(num_active));
				    spawnIndex = num_active;
				}
			}
    }

    T& spawn() {
        if (num_active < this->storage.size()) {
            spawnIndex = num_active++;
        } else
            spawnIndex = ++spawnIndex % this->storage.size();
        return storage.at(spawnIndex);
    }

    int getNumActive() final {
        return num_active;
    }

    void setNumActive(std::size_t i) final {
		    num_active = (i <= storage.size()) ? i : storage.size();
		    spawnIndex = num_active;
    }

};

#endif //RAYLIB_STG_POOLINGVECTOR_H
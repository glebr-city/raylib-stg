//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_POOLINGVECTOR_H
#define RAYLIB_STG_POOLINGVECTOR_H
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstddef>

class IPoolingVector {
public:
    virtual ~IPoolingVector() = default;
    virtual void doPreStep() = 0;
    virtual void doPhysics() = 0;
    virtual void doPhysics(std::array<Vector2, 2> playerPosAndMovement) = 0;
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
    std::vector<T> storage;
    public:
		// Main Constructor
		PoolingVector(T _template, std::size_t size, const int _scoreValue) {
        scoreItemValue = _scoreValue;
        for (int i = 0; i < size; i++) {
            storage.emplace_back(_template);
        }
    }

		// Default constructor
        PoolingVector() : PoolingVector({}, 0, 0) {}
		PoolingVector(std::size_t size) : PoolingVector({}, size, 0) {}

    PoolingVector(T _template, int size): PoolingVector(_template, size, 0) {}

    PoolingVector(std::size_t size, const int _scoreValue) : PoolingVector({}, size, _scoreValue) {}

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
            return elem.getPosition();
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

		void doPhysics(std::array<Vector2, 2> playerPosAndMovement) final {
      auto i = 0UL;  
			while(i < num_active && num_active > 0) {
				if(storage.at(i).doPhysics(playerPosAndMovement)) {
					i++;
				} else {
					num_active--;
					std::swap(storage.at(i), storage.at(num_active));
				}
			}
    }

		void doPhysics() final {
      auto i = 0UL;  
			while(i < num_active && num_active > 0) {
				if(storage.at(i).doPhysics()) {
					i++;
				} else {
					num_active--;
					std::swap(storage.at(i), storage.at(num_active));
				}
			}
    }

    T& spawn() {
        if (num_active >= this->storage.size()) {
            num_active = 0;
        }
        return storage.at(num_active++);
    }

    int getNumActive() final {
        return num_active;
    }

    void setNumActive(std::size_t i) final {
        num_active = (i <= storage.size()) ? i : storage.size();
    }

};

#endif //RAYLIB_STG_POOLINGVECTOR_H
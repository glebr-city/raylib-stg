//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_GAMEOBJECT_H
#define RAYLIB_STG_GAMEOBJECT_H


class GameObjectHandler;

class GameObject {
protected:
    GameObject() = default;
public:
    virtual ~GameObject();
};


#endif //RAYLIB_STG_GAMEOBJECT_H
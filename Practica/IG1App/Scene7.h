#pragma once
#include "Scene.h"

class CompoundEntity;

class Scene7 :
    public Scene
{
public:
    void init() override;
    bool handleKey(unsigned int key) override;
    void rotateTIE();
    void orbitTIE();
private:
    CompoundEntity* Node;
};


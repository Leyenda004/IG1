#pragma once
#include "Scene.h"

class CompoundEntity;

class Scene7 :
    public Scene
{
public:
    void init() override;
    void rotateTIE() override;
    void orbitTIE() override;
private:
    CompoundEntity* Node;
};


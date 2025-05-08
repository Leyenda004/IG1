#pragma once
#include "Scene.h"

class CompoundEntity;
class AdvancedTIE;

class Scene7 :
    public Scene
{
public:
    void init() override;
    bool handleKey(unsigned int key) override;
	void addLights() override;
    void rotateTIE();
    void orbitTIE();
private:
    CompoundEntity* Node;
	AdvancedTIE* FighterTIE = nullptr;

    PosLight* posLight = nullptr;
    SpotLight* spotLight = nullptr;
};
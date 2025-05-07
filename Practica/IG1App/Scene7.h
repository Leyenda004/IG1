#pragma once
#include "Scene.h"

class CompoundEntity;

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
    
    PosLight* posLight = nullptr;
    bool posLightOn = true;
    SpotLight* spotLight = nullptr;
    bool spotLightOn = true;
    SpotLight* foco = nullptr;
    bool focoOn = true;
};
#pragma once
#include "Scene.h"
class Scene9 :
    public Scene
{
public:
    void init() override;
    void addLights() override;
private:
    DirLight* dirLight = nullptr;
};

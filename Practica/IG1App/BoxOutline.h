#pragma once
//#include "SingleColorEntity.h"
#include "EntityWithTexture.h"

class BoxOutline :
    public EntityWithTexture
{
private:
    double length;
public:
    BoxOutline(GLdouble length/* = 100.f*/);
    //void render(const glm::mat4& modelViewMat) const override;
};


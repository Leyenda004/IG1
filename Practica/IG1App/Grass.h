#pragma once
#include "EntityWithTexture.h"
class Grass :
    public EntityWithTexture
{
public:
    Grass(GLdouble width, GLdouble height, GLdouble posX, GLdouble posY, GLdouble posZ, std::string mTexturePar);
    void render(const glm::mat4& modelViewMat) const override;
};


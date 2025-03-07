#pragma once
#include "SingleColorEntity.h"
class Star3D :
    public SingleColorEntity
{
public:
    Star3D(GLdouble re, GLuint np, GLdouble h);
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
};


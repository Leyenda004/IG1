#pragma once
#include "Entity.h"
class RGBCube :
    public EntityWithColors
{
private:
    GLdouble length;
    GLfloat angle = 0.0f;
    GLint index = 0;
public:
    RGBCube(GLdouble length);
    void render(const glm::mat4& modelViewMat) const override;
    void update() override;
};


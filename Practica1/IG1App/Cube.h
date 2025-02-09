#pragma once
#include "SingleColorEntity.h"
class Cube :
    public SingleColorEntity
{
private:
    double length;
public:
    Cube(GLdouble length);
    void render(const glm::mat4& modelViewMat) const override;
};
#pragma once
#include "SingleColorEntity.h"
class Cube :
    public SingleColorEntity
{
public:
    Cube(double);
private:
    double length;
    void render(const glm::mat4& modelViewMat) const override;
};
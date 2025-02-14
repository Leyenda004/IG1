#pragma once
#include "SingleColorEntity.h"
class RegularPolygon :
    public SingleColorEntity
{
private:
    glm::dvec4 color;
    GLuint edges;
    GLdouble radius;
public:
    RegularPolygon(glm::dvec4 color,GLuint edges,GLdouble radius);
};


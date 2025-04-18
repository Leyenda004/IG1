#pragma once
#include "ColorMaterialEntity.h"
class Cone :
    public ColorMaterialEntity
{
public:
    Cone(GLdouble h, GLdouble r, GLdouble R, GLuint nRings = 30, GLuint nSamples = 30);
};


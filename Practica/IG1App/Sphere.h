#pragma once
#include "ColorMaterialEntity.h"
class Sphere :
    public ColorMaterialEntity
{
public:
    Sphere(GLdouble radius, GLuint nParallels = 40, GLuint nMeridians = 40);
};


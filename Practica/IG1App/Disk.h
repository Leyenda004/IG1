#pragma once
#include "ColorMaterialEntity.h"
class Disk
	: public ColorMaterialEntity
{
public:
	Disk(GLdouble R, GLdouble r, GLuint nRings = 30, GLuint nSamples = 30);
};


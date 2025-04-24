#pragma once
#include "ColorMaterialEntity.h"
#include <numbers>
class Disk
	: public ColorMaterialEntity
{
public:
	Disk(GLdouble R, GLdouble r, GLuint nRings = 30, GLuint nSamples = 30, GLfloat angleMax = 2 * std::numbers::pi);
};


#pragma once
#include "ColorMaterialEntity.h"
class Torus
	: public ColorMaterialEntity
{
public:
    //r: grosor
    //R: radio
    //nSamples: numero de muestras
    //nPoints: numero de puntos de la circunferencia
    Torus(GLdouble R, GLdouble r, GLuint nPoints = 30, GLuint nSamples = 30);
};


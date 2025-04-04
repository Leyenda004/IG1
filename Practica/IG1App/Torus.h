#pragma once
#include "SingleColorEntity.h"
class Torus :
    public SingleColorEntity
{
public:
    //r: grosor
    //R: radio
    //nSamples: numero de muestras
    //nPoints: numero de puntos de la circunferencia
    Torus(GLdouble R, GLdouble r, GLuint nPoints = 40, GLuint nSamples = 40);
    
};


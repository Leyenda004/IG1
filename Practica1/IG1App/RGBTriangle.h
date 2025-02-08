#pragma once
#include "Entity.h"
class RGBTriangle : public EntityWithColors
{
private:
	GLdouble radius;
public:
	RGBTriangle(GLdouble radius);
	void update() const override;
};
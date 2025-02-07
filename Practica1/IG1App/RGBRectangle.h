#pragma once
#include "Entity.h"
class RGBRectangle : public EntityWithColors
{
private:
	GLdouble w, h;
public:
	RGBRectangle(GLdouble w, GLdouble h);
	//void render(const glm::mat4& modelViewMat) const override;
};


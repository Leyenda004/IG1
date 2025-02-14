#pragma once
#include "Entity.h"
class RGBTriangle : public EntityWithColors
{
private:
	GLdouble radius;
public:
	RGBTriangle(GLdouble radius);
	void render(const glm::mat4& modelViewMat) const override;
	void update() override;
};
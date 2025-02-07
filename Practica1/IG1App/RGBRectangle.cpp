#include "RGBRectangle.h"

RGBRectangle::RGBRectangle(GLdouble w, GLdouble h) : EntityWithColors() {
	mMesh = Mesh::generateRGBRectangle(w, h);
	load();
}

//void RGBRectangle::render(glm::mat4 const& modelViewMat) const {
//
//}
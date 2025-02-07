#include "RGBTriangle.h"

RGBTriangle::RGBTriangle(GLdouble radius) : EntityWithColors() {
	mMesh = Mesh::generateRGBTriangle(radius);
	//load();
}
#include "Box.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Box::Box() {
	mMesh = Mesh::generateBoxOutlineTexCor(100.f);
	mMeshTapa = Mesh::generateRectangleTexCor(100.f, 100.f);
	mMeshFondo = Mesh::generateRectangleTexCor(100.f, 100.f);

	mat4 rot = rotate(mat4(1.0f), glm::radians(90.f), vec3(1.0f, 0.0f, 0.0f));
	setModelMat(rot * mModelMat);
}
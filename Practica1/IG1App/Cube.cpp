#include "Cube.h"
using namespace glm;

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(GLdouble length) {
	mMesh = Mesh::generateCube(length);
}

void Cube::render(glm::mat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		/*mat4 aMat = modelViewMat * mModelMat;
		mShader->use();
		mShader->setUniform("modelView", aMat);*/
	}
}